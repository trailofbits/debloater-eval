"""Run performance tests on binaries debloated using gtirb-block-trace"""

import argparse
from contextlib import contextmanager
import logging
from pathlib import Path
import re
import shlex
import subprocess
from tempfile import mkdtemp
from debloater_eval.metrics import Metrics

HOST_ROOT_DIR = Path(__file__).parent / ".."
CONTAINER_ROOT_DIR = Path("/debloater_eval")
BENCHMARKS_DIR = CONTAINER_ROOT_DIR / "benchmarks-debloated"
TEST_DIR = CONTAINER_ROOT_DIR / "performance-benchmarks"

IMAGE_NAME = "gtirb-reduce-dynamic"
CONTAINER_NAME = IMAGE_NAME
USER_ID = int(subprocess.check_output("id -u".split()))
GROUP_ID = int(subprocess.check_output("id -g".split()))

PACKAGES = ["libevent-dev", "libssl-dev", "libnss3", "libopenjp2-7-dev", "libtiff-dev", "libpng-dev",
            "libfontconfig-dev", "libjpeg-dev", "libgomp1", "libomp-dev", "python3-pip", "wget", "lftp"]

BINARY_TO_TEST = {
    "low/bzip2/gtirb-dynamic/bzip2.reduced": "benchmark_bzip2.sh",
    "low/chown/gtirb-dynamic/chown.reduced": "benchmark_chown.sh",
    "low/date/gtirb-dynamic/date.reduced": "benchmark_date.sh",
    "low/grep/gtirb-dynamic/grep.reduced": "benchmark_grep.sh",
    "low/gzip//gtirb-dynamic/gzip.reduced": "benchmark_gzip.sh",
    "low/mkdir/gtirb-dynamic/mkdir.reduced": "benchmark_mkdir.sh",
    "low/rm/gtirb-dynamic/rm.reduced": "benchmark_rm.sh",
    "low/sort/gtirb-dynamic/sort.reduced": "benchmark_sort.sh",
    "low/tar/gtirb-dynamic/tar.reduced": "benchmark_tar.sh",
    "low/uniq/gtirb-dynamic/uniq.reduced": "benchmark_uniq.sh",
    "medium/make/gtirb-dynamic/make.reduced": "benchmark_make.sh",
    "medium/memcached/gtirb-dynamic/memcached.reduced": "benchmark_memcached.sh",
    "medium/objdump/gtirb-dynamic/objdump.reduced": "benchmark_objdump.sh",
    "medium/wget/gtirb-dynamic/wget.reduced": "benchmark_wget.sh",
    "high/imagemagick/gtirb-dynamic/magick.reduced": "benchmark_imagemagick.sh",
    "high/nginx/gtirb-dynamic/nginx.reduced": "benchmark_nginx.sh",
    "high/nmap/gtirb-dynamic/nmap.reduced": "benchmark_nmap.sh",
    "high/poppler/gtirb-dynamic/pdftohtml.reduced": "benchmark_pdftohtml.sh",
}


def run_as_root(binary_name):
    """Check whether performance test should be run as root"""
    return binary_name != "memcached"


def install_dependencies(container):
    """Install dependencies"""
    # Packages
    dexec(container, "apt-get update -y", as_root=True)
    for package in PACKAGES:
        dexec(container, f"apt-get install -y {package}", as_root=True)

    # Python package for memcached
    dexec(container, "pip3 install python-memcached", as_root=True)

    # Libraries for imagemagick and poppler"""
    libs = {CONTAINER_ROOT_DIR / "benchmarks/high/imagemagick-7.0.1-0/binaries/64/libMagickCore-7.Q16HDRI.so.0.0.0": "libMagickCore-7.Q16HDRI.so.0",
            CONTAINER_ROOT_DIR / "benchmarks/high/imagemagick-7.0.1-0/binaries/64/libMagickWand-7.Q16HDRI.so.0.0.0": "libMagickWand-7.Q16HDRI.so.0",
            CONTAINER_ROOT_DIR / "benchmarks/high/poppler-0.60/binaries/64/libpoppler.so.70.0.0": "libpoppler.so.70"}
    for lib_path, alias in libs.items():
        lib = lib_path.name
        dexec(container, f"cp {lib_path} /usr/lib/x86_64-linux-gnu/", as_root=True)
        dexec(container, f"ln -s {lib} {alias}", working_dir="/usr/lib/x86_64-linux-gnu/", as_root=True)


def get_image():
    """Build docker image for gtirb-reduce-dynamic"""
    cmd = f"docker build --file Dockerfile --network=host -t {IMAGE_NAME} ."
    subprocess.run(shlex.split(cmd), check=True)


def dexec(container, cmd, as_root=False, working_dir=""):
    """Execute command on docker container"""
    user_string = f"-u {USER_ID}:{GROUP_ID} " if not as_root else ""
    wdir_string = f"--workdir {working_dir}" if working_dir else ""
    subprocess.run(shlex.split(f"docker exec {wdir_string} {user_string} {container} {cmd}"), check=True)


@contextmanager
def run_container(working_dir):
    """Context manager for running docker container"""
    cmd = (
        f"docker run -d --network=host --name {CONTAINER_NAME} "
        f"-itv {HOST_ROOT_DIR.absolute()}:/{CONTAINER_ROOT_DIR} "
        f"-w {working_dir} "
        f"-e MAGICK_CONFIGURE_PATH={CONTAINER_ROOT_DIR / 'benchmarks/high/imagemagick-7.0.1-0/binaries/64/'} "
        f"{IMAGE_NAME} tail -f /dev/null"
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
    args = parser.parse_args()
    binary_metrics = Metrics(output_dir=Path(mkdtemp()))
    get_image()

    for binary_path, test_path in BINARY_TO_TEST.items():
        if not re.search(args.benchmark_regex, binary_path):
            continue
        print(f"Processing {binary_path}")
        with run_container(TEST_DIR) as container:
            binary_path = CONTAINER_ROOT_DIR / BENCHMARKS_DIR / binary_path
            binary_name = binary_path.name.split(".")[0]
            dexec(container, f"ls {binary_path}")
            test_path = Path(test_path)
            dexec(container, f"ls {test_path}")
            install_dependencies(container)

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
