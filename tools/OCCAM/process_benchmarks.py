"""Debloat benchmarks using OCCAM and test debloated binaries"""
import argparse
from contextlib import contextmanager
import logging
from pathlib import Path
import re
import shlex
import subprocess
import sys
from tempfile import mkdtemp
import traceback

import yaml

from debloater_eval.metrics import Metrics

# Common config
OCCAM = "occam"
BENCHMARKS_DIRNAME = "benchmarks"
SPECS_DIRNAME = "tool-debloating-specs"
SPECS_FILENAME = "occam.manifest"
ORIGINAL = "original"
DEBLOATED = "debloated"

# Host config
HOST_ROOT_DIR = Path(__file__).parent / ".."
BENCHMARKS_YML_PATH = Path(__file__).parent / "benchmarks.yml"
HOST_DEBLOATED_BINARIES_DIR = HOST_ROOT_DIR / "benchmarks-debloated/"

# Container config
IMAGE_NAME = " sricsl/occam:bionic"
CONTAINER_NAME = "occam"
USER_ID = int(subprocess.check_output("id -u".split()))
GROUP_ID = int(subprocess.check_output("id -g".split()))
CONTAINER_ROOT_DIR = Path("/debloater_eval")
CONTAINER_BENCHMARKS_DIRNAME = "benchmarks-container"
CONTAINER_BENCHMARKS_DIR = CONTAINER_ROOT_DIR / CONTAINER_BENCHMARKS_DIRNAME
CONTAINER_SPECS_DIR = CONTAINER_ROOT_DIR / SPECS_DIRNAME
CONTAINER_PERF_TEST_DIR = CONTAINER_ROOT_DIR / "performance-benchmarks"

# Metrics
tool_metrics = Metrics(output_dir=Path(mkdtemp()))
binary_metrics = Metrics(output_dir=Path(mkdtemp()))


def get_image():
    """Get docker image for OCCAM"""
    cmd = "docker pull sricsl/occam:bionic"
    subprocess.run(shlex.split(cmd), check=True)


@contextmanager
def run_container(working_dir, cut_args):
    """Context manager for running LMCAS docker container"""
    cmd = (
        f"docker run -d --network=host --name {CONTAINER_NAME} "
        f"-itv {HOST_ROOT_DIR.absolute()}:/{CONTAINER_ROOT_DIR} "
        f"-w {working_dir} -e CUT_ARGS={str(cut_args).lower()} "
        f"{IMAGE_NAME} tail -f /dev/null"
    )
    cmd = shlex.split(cmd)
    logging.info(cmd)
    subprocess.run(cmd, check=True)
    try:
        dexec(CONTAINER_NAME, "chmod a=rwx,u+t /tmp", as_root=True)  # Fix /tmp permissions to allow non-root users to create temp directories
        dexec(CONTAINER_NAME, "apt-get install -y time", as_root=True)  # Install /usr/bin/time to collect metrics
        yield CONTAINER_NAME
    finally:
        subprocess.run(["docker", "container", "rm", "-f", CONTAINER_NAME], stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=True)


def dexec(container, cmd, as_root=False, working_dir=""):
    """Execute command on docker container"""
    user_string = f"-u {USER_ID}:{GROUP_ID} " if not as_root else ""
    wdir_string = f"--workdir {working_dir}" if working_dir else ""
    subprocess.run(shlex.split(f"docker exec {wdir_string} {user_string} {container} {cmd}"), check=True)


def process_benchmark(args, config, benchmark_name):
    """Process benchmark"""
    benchmark_config = config[benchmark_name]
    working_dir = CONTAINER_BENCHMARKS_DIR / benchmark_name / "occam_x64_bin"
    benchmark_id = benchmark_config["id"]
    binary_name = benchmark_config["binary-name"]
    complexity = benchmark_config["complexity"]
    packages = benchmark_config.get("packages", [])
    libs = benchmark_config.get("libs", {})
    pip_modules = benchmark_config.get("pip-modules", [])
    original_binary_path = working_dir / binary_name
    debloated_binary_path = working_dir / benchmark_config["debloated-binary-name"]
    perf_test_script = benchmark_config.get("perf-test-script", f"benchmark_aggressive_{benchmark_id}.sh")
    as_root = benchmark_config.get("perf-test-run-as-root", True)

    with run_container(working_dir, cut_args=(args.perf_test_target == DEBLOATED)) as container:
        # Install dependencies
        install_dependencies(container, packages, libs, pip_modules)

        # Run debloater with spec
        if not args.no_debloat:
            debloat_benchmark(container, working_dir, benchmark_id, binary_name, complexity)

        # Save debloated binary to host
        if not args.no_save_binaries:
            output_dir = HOST_DEBLOATED_BINARIES_DIR / complexity / benchmark_id / OCCAM
            output_dir.mkdir(parents=True, exist_ok=True)
            cmd = f"docker cp {container}:{debloated_binary_path} {output_dir}"
            subprocess.run(shlex.split(cmd), check=True)

        # Run performance test on original/debloated binary
        if not args.no_perf:
            perf_test_binary_path = debloated_binary_path if args.perf_test_target == DEBLOATED else original_binary_path
            run_performance_test(container, benchmark_id, perf_test_binary_path, perf_test_script, as_root)


def install_dependencies(container, packages, libs, pip_modules):
    """Install package/library/Python dependencies for benchmark, if any"""
    for package in packages:
        logging.info(f"Installing package {package}...")
        dexec(CONTAINER_NAME, f"apt-get install -y {package}", as_root=True)
    for lib, alias in libs.items():
        dexec(container, f"cp {lib} /usr/lib/x86_64-linux-gnu/", as_root=True)
        dexec(container, f"ln -s {lib} {alias}", working_dir="/usr/lib/x86_64-linux-gnu/", as_root=True)
    for module in pip_modules:
        dexec(container, f"pip3 install {module}", as_root=True)


def debloat_benchmark(container, working_dir, benchmark_id, binary_name, complexity):
    """Debloat benchmark if specs are available"""
    logging.info(f"Debloating benchmark {benchmark_id}")

    binary_path = working_dir / binary_name
    dexec(container, f"ls {binary_path}")
    specs_path = CONTAINER_SPECS_DIR / complexity / benchmark_id / SPECS_FILENAME
    dexec(container, f"ls {specs_path}")

    # Debloat binary
    cmd = f"slash {specs_path}"
    cmds, metrics_path = tool_metrics.get_commands_with_metrics(cmd, benchmark_id)
    try:
        for cmd in cmds:
            logging.info(cmd)
            dexec(container, cmd)
    finally:
        copy_metrics_to_host(container, metrics_path)


def run_performance_test(container, benchmark_id, binary_path, perf_test_script, as_root):
    """Run performance test on benchmark"""
    logging.info(f"Running performance test on benchmark {benchmark_id}")

    dexec(container, f"ls {binary_path}")
    dexec(container, f"ls {perf_test_script}", working_dir=CONTAINER_PERF_TEST_DIR)

    cmd = f"./{perf_test_script} {binary_path}"
    cmds, metrics_path = binary_metrics.get_commands_with_metrics(cmd, benchmark_id)
    try:
        for cmd in cmds:
            logging.info(cmd)
            dexec(container, cmd, as_root=as_root, working_dir=CONTAINER_PERF_TEST_DIR)
    finally:
        copy_metrics_to_host(container, metrics_path)


def copy_metrics_to_host(container, metrics_path):
    """Copy metrics file to host"""
    metrics_path.parent.mkdir(parents=True, exist_ok=True)
    cmd = f"docker cp {container}:{metrics_path} {metrics_path}"
    logging.info(cmd)
    subprocess.run(shlex.split(cmd), check=True)


def load_config():
    """Load benchmark config from yml file"""
    with BENCHMARKS_YML_PATH.open(encoding="utf-8") as yaml_file:
        config = yaml.safe_load(yaml_file.read())
        return config


def copy_benchmarks():
    """Copy benchmarks to new directory to avoid contaminating source directory"""
    source_dir = HOST_ROOT_DIR / BENCHMARKS_DIRNAME
    target_dir = HOST_ROOT_DIR / CONTAINER_BENCHMARKS_DIRNAME
    if not target_dir.exists():
        cmd = f"cp -r {source_dir} {target_dir}"
        logging.info(cmd)
        subprocess.run(shlex.split(cmd), check=True)
    else:
        logging.warning(f"{target_dir} already exists. Delete or move it to update files.")


def main():
    """Debloat benchmarks using OCCAM and test debloated binaries"""
    parser = argparse.ArgumentParser()
    group = parser.add_mutually_exclusive_group()
    group.add_argument("--list", action="store_true", help="List all benchmarks.")
    group.add_argument(
        "-b",
        dest="benchmark_regex",
        default=".*",
        help="Process benchmarks which match the given regex. If no regex is provided, all benchmarks will be processed",
    )
    parser.add_argument("--no-debloat", dest="no_debloat", action="store_true",
                        help="Disable benchmark debloating")
    parser.add_argument("--no-performance-tests", dest="no_perf", action="store_true",
                        help="Disable running performance tests on debloated binaries")
    parser.add_argument("--perf-test-target", dest="perf_test_target", choices=[ORIGINAL, DEBLOATED],
                        default=DEBLOATED, help=f"Target binaries for performance test, default {DEBLOATED}.")
    parser.add_argument("--no-save-binaries", dest="no_save_binaries", action="store_true",
                        help="Disable saving debloated binaries to repository")
    parser.add_argument("--tool-metrics-filename", dest="tool_metrics_filename", default="tool_metrics.csv",
                        help="Output file where debloating metrics are saved")
    parser.add_argument("--binary-metrics-filename", dest="binary_metrics_filename", default="binary_metrics.csv",
                        help="Output file where performance test metrics are saved")
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

    config = load_config()
    benchmark_names = list(config.keys())

    if args.list:
        for benchmark_name in benchmark_names:
            logging.info(benchmark_name)
        return

    get_image()
    copy_benchmarks()

    re_benchmarks = re.compile(args.benchmark_regex)
    to_process = [benchmark_name for benchmark_name in benchmark_names if re_benchmarks.search(benchmark_name)]

    if not to_process:
        raise ValueError(f"No benchmarks found matching regex {args.benchmark_regex}")

    successes = []
    failures = []

    for benchmark_name in to_process:
        logging.info(f"Processing benchmark: {benchmark_name}")
        try:
            process_benchmark(args, config, benchmark_name)
            successes.append(benchmark_name)
        except Exception as error:
            logging.error(f"Failed to process {benchmark_name}: {error}")
            traceback.print_exc()
            failures.append(benchmark_name)

    tool_metrics.collect_metrics(output_csv_path=Path(args.tool_metrics_filename))
    binary_metrics.collect_metrics(output_csv_path=Path(args.binary_metrics_filename))
    logging.info(f"\nSuccessfully processed benchmarks: {successes}\n")
    logging.info(f"\nFailed to process benchmarks: {failures}\n")


if __name__ == "__main__":
    main()
