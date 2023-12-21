"""Run performance tests on original binaries"""

import argparse
from contextlib import contextmanager
import logging
from pathlib import Path
import re
import shlex
import subprocess
import sys
from tempfile import mkdtemp
from debloater_eval.metrics import Metrics

HOST_ROOT_DIR = Path(__file__).parent / ".."
CONTAINER_ROOT_DIR = Path("/debloater_eval")
BENCHMARKS_DIR = CONTAINER_ROOT_DIR / "benchmarks"
TEST_DIR = CONTAINER_ROOT_DIR / "performance-benchmarks"

IMAGE_NAME = "original-binaries"
CONTAINER_NAME = IMAGE_NAME
USER_ID = int(subprocess.check_output("id -u".split()))
GROUP_ID = int(subprocess.check_output("id -g".split()))

GENERAL = "general"
AGGRESSIVE = "aggressive"
UBUNTU = "ubuntu"
DEBIAN_BUSTER = "debian-buster"
OS_TO_DOCKERFILE = {UBUNTU: "Dockerfile", DEBIAN_BUSTER: "Dockerfile.buster"}
OS_TO_DIRNAME = {UBUNTU: "64", DEBIAN_BUSTER: "buster"}

BINARY_TO_TEST = {
    "low/bzip2-1.0.5/binaries/os_dirname/bzip2": "benchmark_bzip2.sh",
    "low/chown-8.2/binaries/os_dirname/chown": "benchmark_chown.sh",
    "low/date-8.21/binaries/os_dirname/date": "benchmark_date.sh",
    "low/grep-2.19/binaries/os_dirname/grep": "benchmark_grep.sh",
    "low/gzip-1.2.4/binaries/os_dirname/gzip": "benchmark_gzip.sh",
    "low/mkdir-5.2.1/binaries/os_dirname/mkdir": "benchmark_mkdir.sh",
    "low/rm-8.4/binaries/os_dirname/rm": "benchmark_rm.sh",
    "low/sort-8.16/binaries/os_dirname/sort": "benchmark_sort.sh",
    "low/tar-1.14/binaries/os_dirname/tar": "benchmark_tar.sh",
    "low/uniq-8.16/binaries/os_dirname/uniq": "benchmark_uniq.sh",
    "medium/bftpd-6.1/binaries/os_dirname/bftpd": "benchmark_bftpd.sh",
    "medium/lighttpd-1.4/binaries/os_dirname/lighttpd": "benchmark_lighttpd.sh",
    "medium/make-4.2/binaries/os_dirname/make": "benchmark_make.sh",
    "medium/memcached-1.6.18/binaries/os_dirname/memcached": "benchmark_memcached.sh",
    "medium/binutils-2.40/binaries/os_dirname/objdump": "benchmark_objdump.sh",
    "medium/wget-1.20.3/binaries/os_dirname/wget": "benchmark_wget.sh",
    "high/imagemagick-7.0.1-0/binaries/os_dirname/magick": "benchmark_imagemagick.sh",
    "high/nginx-1.23.3/binaries/os_dirname/nginx": "benchmark_nginx.sh",
    "high/nmap-7.93/binaries/os_dirname/nmap": "benchmark_nmap.sh",
    "high/poppler-0.60/binaries/os_dirname/pdftohtml": "benchmark_pdftohtml.sh",
}


def run_as_root(binary_name):
    """Check whether performance test should be run as root"""
    return binary_name != "memcached"


def install_libraries(container, os):
    """Install libraries for imagemagick and poppler"""
    os_dirname = OS_TO_DIRNAME[os]
    libs = {CONTAINER_ROOT_DIR / f"benchmarks/high/imagemagick-7.0.1-0/binaries/{os_dirname}/libMagickCore-7.Q16HDRI.so.0.0.0": "libMagickCore-7.Q16HDRI.so.0",
            CONTAINER_ROOT_DIR / f"benchmarks/high/imagemagick-7.0.1-0/binaries/{os_dirname}/libMagickWand-7.Q16HDRI.so.0.0.0": "libMagickWand-7.Q16HDRI.so.0",
            CONTAINER_ROOT_DIR / f"benchmarks/high/poppler-0.60/binaries/{os_dirname}/libpoppler.so.70.0.0": "libpoppler.so.70"}
    for lib_path, alias in libs.items():
        lib = lib_path.name
        dexec(container, f"cp {lib_path} /usr/lib/x86_64-linux-gnu/", as_root=True)
        dexec(container, f"ln -s {lib} {alias}", working_dir="/usr/lib/x86_64-linux-gnu/", as_root=True)


def get_image(os):
    """Build docker image for testing binaries"""
    cmd = f"docker build --file {OS_TO_DOCKERFILE[os]} --network=host -t {IMAGE_NAME}-{os} ."
    subprocess.run(shlex.split(cmd), check=True)


def dexec(container, cmd, as_root=False, working_dir=""):
    """Execute command on docker container"""
    user_string = f"-u {USER_ID}:{GROUP_ID} " if not as_root else ""
    wdir_string = f"--workdir {working_dir}" if working_dir else ""
    subprocess.run(shlex.split(f"docker exec {wdir_string} {user_string} {container} {cmd}"), check=True)


@contextmanager
def run_container(working_dir, os):
    """Context manager for running docker container"""
    os_dirname = OS_TO_DIRNAME[os]
    cmd = (
        f"docker run -d --network=host --name {CONTAINER_NAME} "
        f"-itv {HOST_ROOT_DIR.absolute()}:/{CONTAINER_ROOT_DIR} "
        f"-w {working_dir} "
        f"-e MAGICK_CONFIGURE_PATH={CONTAINER_ROOT_DIR / 'benchmarks/high/imagemagick-7.0.1-0/binaries' / os_dirname} "
        f"{IMAGE_NAME}-{os} tail -f /dev/null"
    )
    cmd = shlex.split(cmd)
    logging.info(cmd)
    subprocess.run(cmd, check=True)
    try:
        yield CONTAINER_NAME
    finally:
        subprocess.run(["docker", "container", "rm", "-f", CONTAINER_NAME], stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=True)


def copy_metrics_to_host(container, metrics_path):
    """Copy metrics file to host"""
    metrics_path.parent.mkdir(parents=True, exist_ok=True)
    cmd = f"docker cp {container}:{metrics_path} {metrics_path}"
    logging.info(cmd)
    subprocess.run(shlex.split(cmd), check=True)


def main():
    """Main"""
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-b",
        dest="benchmark_regex",
        default=".*",
        help="Process benchmarks which match the given regex. If no regex is provided, all benchmarks will be processed",
    )
    parser.add_argument("--type", choices=[GENERAL, AGGRESSIVE], default=GENERAL,
                        help="Type of performance test to run, default general.")
    parser.add_argument("--os", choices=[UBUNTU, DEBIAN_BUSTER], default=UBUNTU,
                        help="OS for dockerfile to use, default ubuntu.")
    parser.add_argument("--log", default=2, type=int, choices=[0, 1, 2, 3, 4, 5],
                        help="0:all, 1:debug, 2:info, 3:warning, 4:error, 5:critical")
    args = parser.parse_args()

    log_level = args.log * 10
    logging.basicConfig(
        format="%(asctime)s %(levelname)-8s [%(funcName)s][%(filename)s:%(lineno)d] %(message)s",
        datefmt="%H:%M:%S",
        stream=sys.stdout,
        level=log_level,
        force=True,
    )

    binary_metrics = Metrics(output_dir=Path(mkdtemp()))
    get_image(args.os)
    os_dirname = OS_TO_DIRNAME[args.os]

    for binary_path, test_path in BINARY_TO_TEST.items():
        if not re.search(args.benchmark_regex, binary_path):
            continue
        binary_path = binary_path.replace("os_dirname", os_dirname)
        print(f"Processing {binary_path}")
        with run_container(TEST_DIR, args.os) as container:
            binary_path = CONTAINER_ROOT_DIR / BENCHMARKS_DIR / binary_path
            binary_name = binary_path.name.split(".")[0]
            dexec(container, f"ls {binary_path}")
            if args.type == AGGRESSIVE:
                test_path = test_path.replace("benchmark_", f"benchmark_{AGGRESSIVE}_")
            test_path = Path(test_path)
            dexec(container, f"ls {test_path}")
            install_libraries(container, args.os)

            cmd = f"./{test_path} {binary_path}"
            cmds, metrics_path = binary_metrics.get_commands_with_metrics(cmd, binary_name)
            try:
                for cmd in cmds:
                    logging.info(cmd)
                    dexec(container, cmd, as_root=run_as_root(binary_name))
            except Exception as exception:
                logging.error(exception)
            finally:
                copy_metrics_to_host(container, metrics_path)

    binary_metrics.collect_metrics(output_csv_path=Path("binary_metrics.csv"))


if __name__ == "__main__":
    main()
