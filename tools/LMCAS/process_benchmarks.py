"""Build and debloat benchmarks using LMCAS and test debloated binaries"""
import multiprocessing
import shlex
import subprocess
from pathlib import Path
from contextlib import contextmanager
import argparse
import re
from tempfile import mkdtemp

import yaml

from debloater_eval.metrics import Metrics

# Common config
LMCAS = "lmcas"
BUILDS_DIRNAME = "builds"  # benchmarks copied here to avoid contaminating repository
SPECS_DIRNAME = "specs"  # specs copied here to avoid contaminating repository
ALL_BENCHMARK_COMPLEXITIES = ("low", "medium", "high")
SPECS_FILENAME = "lmcas_specs.json"
INPUT_FILES_DIRNAME = "input_files"
NON_DEBLOATED_BINARY_NAME = "nondebloated"
DEBLOATED_BINARY_NAME = "debloated"
ORIGINAL = "original"
DEBLOATED = DEBLOATED_BINARY_NAME

# Host config
ROOT_DIR = Path(__file__).parent / ".."
BENCHMARKS_YML_PATH = Path(__file__).parent / "benchmarks.yml"
HOST_BENCHMARKS_DIR = ROOT_DIR / "benchmarks/"
HOST_SPECS_DIR = ROOT_DIR / "tool-debloating-specs"
HOST_DEBLOATED_BINARIES_DIR = ROOT_DIR / "benchmarks-debloated/"

# Container config
IMAGE_NAME = "docker.tpcp.io/metis/lmcas/lmcas-deliv:2023-04-10@sha256:7875dabb6e10adac4087f31dc503143a3f3e20a5be1ce2920f1e62ad5f7969c5"
CONTAINER_NAME = "lmcas"
BUILDS_DIR = Path(f"/debloater-eval/{BUILDS_DIRNAME}")
USER_ID = int(subprocess.check_output("id -u".split()))
GROUP_ID = int(subprocess.check_output("id -g".split()))
SPECS_DIR = Path("/debloater-eval") / SPECS_DIRNAME
# Markers in specs replaced by container-specific paths
BINARY_PATH_MARKER = "{BINARY_PATH}"
INPUT_FILES_PATH_MARKER = "{INPUT_FILES_PATH}"
CWD_MARKER = "{CWD}"
PERFORMANCE_TEST_DIR = Path("/debloater-eval/performance-benchmarks")

# Compilation flags
COMPILE_FLAGS = "-O3 -fPIC -fPIE"
LINK_FLAGS = "-pie"
MARKERS_MAP = {"{COMPILE_FLAGS}": COMPILE_FLAGS, "{LINK_FLAGS}": LINK_FLAGS, "{NPROC}": str(multiprocessing.cpu_count())}

# Metrics
tool_metrics = Metrics(time_command="/bin/time", output_dir=Path(mkdtemp()))
binary_metrics = Metrics(time_command="/bin/time", output_dir=Path(mkdtemp()))


@contextmanager
def run_container(working_dir, env_vars):
    """Context manager for running LMCAS docker container"""
    env_args = [f'--env {name}="{value}"' for name, value in env_vars.items()]
    cmd = (
        f"docker run -d --network=host --name {CONTAINER_NAME} "
        f"-itv {ROOT_DIR.absolute()}:/debloater-eval "
        f"-w {working_dir} {' '.join(env_args)} "
        f"{IMAGE_NAME} tail -f /dev/null"
    )
    cmd = shlex.split(cmd)
    print(cmd)
    subprocess.run(cmd, check=True)
    try:
        dexec(CONTAINER_NAME, "chmod a=rwx,u+t /tmp", as_root=True)  # fix /tmp permissions to allow non-root users to create temp directories
        dexec(CONTAINER_NAME, "chmod a=rwx,u+t /usr", as_root=True)  # fix /usr permissions to allow non-root users to install packages to /usr/local
        dexec(CONTAINER_NAME, f"chmod a=rwx,u+t {working_dir}", as_root=True)  # fix working directory permissions in case created by docker run
        # Add user 'nobody' manually for nginx perf test; useradd doesn't work due to permissions and chattr isn't available to change them
        dexec(CONTAINER_NAME, "sh -c 'echo nobody:x:65534:65534:nobody:/nonexistent:/usr/sbin/nologin >> /etc/passwd'", as_root=True)
        yield CONTAINER_NAME
    finally:
        subprocess.run(["docker", "container", "rm", "-f", CONTAINER_NAME], stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=True)


def dexec(container, cmd, as_root=False, working_dir=""):
    """Execute command on docker container"""
    user_string = f"-u {USER_ID}:{GROUP_ID} " if not as_root else ""
    wdir_string = f"--workdir {working_dir}" if working_dir else ""
    subprocess.run(shlex.split(f"docker exec {wdir_string} {user_string} {container} {cmd}"), check=True)


def replace_markers(string):
    """Replace the {COMPILE_FLAGS}, etc. markers in the yml file."""
    for key, value in MARKERS_MAP.items():
        string = string.replace(key, value)
    return string


def build_benchmark(benchmark_name, container, working_dir, config_map):
    """Build benchmark and dependencies"""
    print(f"Building benchmark: {benchmark_name}")
    benchmark_config = config_map[benchmark_name]

    # Build and install dependencies
    package_tarball_dirname = benchmark_config.get("package-tarball-dir", "")
    package_tarball_dir = (BUILDS_DIR / benchmark_name / package_tarball_dirname) if package_tarball_dirname else working_dir
    for package_name in benchmark_config.get("packages", []):
        build_package(package_name, config_map, container, tarball_dir=package_tarball_dir)

    # Build benchmark
    for stage in ["source-cmd", "patch-cmd", "pre-build", "build", "install"]:
        for cmd in benchmark_config.get(stage, []):
            cmd = replace_markers(cmd)
            print(cmd)
            as_root = stage == "install"
            dexec(container, cmd, as_root=as_root)


def build_package(package_name, config_map, container, tarball_dir):
    """Build and install package"""
    package_config = config_map[package_name]
    # Set up source
    tarball = package_config["tarball"]
    package_dir = BUILDS_DIR / "packages" / package_name
    setup_cmds = [f"mkdir -p {package_dir.as_posix()}", f"cp {tarball_dir.as_posix()}/{tarball} {package_dir.as_posix()}/"]
    for cmd in setup_cmds:
        cmd = replace_markers(cmd)
        print(cmd)
        dexec(container, cmd)

    # Build package
    for stage in ["source-cmd", "pre-build", "build", "install"]:
        for cmd in package_config.get(stage, []):
            cmd = replace_markers(cmd)
            print(cmd)
            dexec(container, cmd, working_dir=package_dir.as_posix())


def process_benchmark(args, benchmark_name, config_map):
    """Process benchmark"""
    # Configure environment
    benchmark_config = config_map[benchmark_name]
    benchmark_config["env"] = {key: replace_markers(value) for key, value in benchmark_config["env"].items()}
    working_dir = BUILDS_DIR / benchmark_name / benchmark_config["source-dir"]
    binary_name = benchmark_config["binaries"][0]

    with run_container(working_dir, benchmark_config["env"]) as container:
        # Build benchmark
        if not args.no_build:
            build_benchmark(benchmark_name, container, working_dir, config_map)

        # Save built binaries to host
        if not args.no_save_binaries:
            output_dir = HOST_BENCHMARKS_DIR / benchmark_name / LMCAS
            output_dir.mkdir(parents=True, exist_ok=True)
            binary_path = working_dir / binary_name
            subprocess.run(f"docker cp {container}:{binary_path} {output_dir}".split(), check=True)

        # Run debloater on spec
        if not args.no_debloat:
            debloat_benchmark(benchmark_name, container, working_dir, benchmark_config, dry_run=not args.no_dry_run)

        # Save debloated binaries to host
        if not args.no_save_binaries:
            debloated_binary_dir = benchmark_config.get("debloated-binary-dir", benchmark_name.split("-")[0])
            output_dir = HOST_DEBLOATED_BINARIES_DIR / debloated_binary_dir / LMCAS
            output_dir.mkdir(parents=True, exist_ok=True)
            debloated_binary_output_name = binary_name.split("/")[-1]  # strip complexity
            debloated_binary_output_path = output_dir / f"{debloated_binary_output_name}_{LMCAS}"
            debloated_binary_input_path = working_dir / DEBLOATED_BINARY_NAME
            subprocess.run(f"docker cp {container}:{debloated_binary_input_path} {debloated_binary_output_path}".split(), check=True)

        # Performance test on debloated binaries
        if not args.no_perf:
            run_performance_test(benchmark_name, container, working_dir, benchmark_config, args.perf_test_target)


def debloat_benchmark(benchmark_name, container, working_dir, benchmark_config, dry_run=True):
    """Debloat benchmark if specs are available"""
    binary_name = benchmark_config["binaries"][0]
    benchmark_name_stem = benchmark_name.split("-")[0]
    specs_subdir = benchmark_config.get("specs-dir", benchmark_name_stem)
    host_specs_dir = HOST_SPECS_DIR / specs_subdir

    # Verify that benchmark spec directory exists
    assert host_specs_dir.exists()
    benchmark_specs_dir = SPECS_DIR / specs_subdir
    cmd = f"ls {benchmark_specs_dir.as_posix()}"
    dexec(container, cmd)

    # Update binary path in specs if available
    host_specs_path = HOST_SPECS_DIR / specs_subdir / SPECS_FILENAME
    if not host_specs_path.exists():
        print(f"ERROR: No specs found for benchmark {benchmark_name} in path {host_specs_path.resolve()}, debloating will fail.")
    binary_path = working_dir / binary_name
    specs_path = SPECS_DIR / specs_subdir / SPECS_FILENAME
    complexity = specs_subdir.split("/")[0]
    input_files_dir_path = SPECS_DIR / complexity / INPUT_FILES_DIRNAME

    update_specs(container, specs_path, binary_path, input_files_dir_path, working_dir)

    # Run debloater on specs
    if dry_run:
        # Dry run
        try:
            cmd = f"tabacco -O3 -o {NON_DEBLOATED_BINARY_NAME} -N {specs_path.as_posix()}"
            print(cmd)
            dexec(container, cmd)
        except Exception as error:
            print(f"Dry run failed for {benchmark_name}, debloating is expected to fail.")
            print(error)
    # Debloat
    cmd = f"tabacco -O3 -o {DEBLOATED_BINARY_NAME} {specs_path.as_posix()}"
    cmds, metrics_path = tool_metrics.get_commands_with_metrics(cmd, binary_name.split("/")[-1])
    try:
        for cmd in cmds:
            print(cmd)
            dexec(container, cmd)
    finally:
        copy_metrics_to_host(container, metrics_path)


def update_specs(container, specs_path, binary_path, input_files_dir_path, working_dir):
    """Update paths in specs"""
    # Verify that binary exists
    cmd = f"ls {binary_path.as_posix()}"
    try:
        dexec(container, cmd)
    except subprocess.CalledProcessError as error:
        print(f"\nERROR: Binary {binary_path.resolve()} not found in container")
        raise error
    # Update paths in specs
    for marker, path in {BINARY_PATH_MARKER: binary_path, INPUT_FILES_PATH_MARKER: input_files_dir_path, CWD_MARKER: working_dir}.items():
        # Update path in specs
        path_escaped = path.as_posix().replace("/", "\/")  # pylint: disable = anomalous-backslash-in-string
        cmd = f"sed -i 's/{marker}/{path_escaped}/' {specs_path}"
        print(cmd)
        dexec(container, cmd)


def run_performance_test(benchmark_name, container, working_dir, benchmark_config, perf_test_target):
    """Run performance test on benchmark"""
    # Set up performance tests
    for cmd in benchmark_config.get("pre-perf-test", []):
        print(cmd)
        dexec(container, cmd, as_root=True)
    print(f"Running performance test on benchmark {benchmark_name}")

    test_script = f"benchmark_aggressive_{benchmark_config['binaries'][0].split('/')[-1]}.sh"
    binary_path = f"{working_dir}/{DEBLOATED_BINARY_NAME}" if perf_test_target == DEBLOATED else f"{working_dir}/{benchmark_config['binaries'][0]}"
    cmd = f"./{test_script} {binary_path}"
    binary_name = benchmark_config["binaries"][0].split("/")[-1]  # strip complexity
    cmds, metrics_path = binary_metrics.get_commands_with_metrics(cmd, binary_name)
    try:
        for cmd in cmds:
            print(cmd)
            dexec(container, cmd, as_root=True, working_dir=PERFORMANCE_TEST_DIR.as_posix())
    finally:
        copy_metrics_to_host(container, metrics_path)


def copy_metrics_to_host(container, metrics_path):
    """Copy metrics file to host"""
    metrics_path.parent.mkdir(parents=True, exist_ok=True)
    cmd = f"docker cp {container}:{metrics_path} {metrics_path}"
    print(cmd)
    subprocess.run(shlex.split(cmd), check=True)


def load_config():
    """Load benchmark config from yml file"""
    with BENCHMARKS_YML_PATH.open(encoding="utf-8") as yaml_file:
        config = yaml.safe_load(yaml_file.read())
        return config


def copy_benchmarks_and_specs():
    """Copy builds/specs to new directory to avoid contaminating repository"""
    builds_dir = ROOT_DIR / BUILDS_DIRNAME
    specs_dir = ROOT_DIR / SPECS_DIRNAME
    dir_map = {HOST_BENCHMARKS_DIR: builds_dir, HOST_SPECS_DIR: specs_dir}
    for source_dir, target_dir in dir_map.items():
        if not target_dir.exists():
            cmd = f"cp -r {source_dir} {target_dir}"
            print(cmd)
            subprocess.run(cmd.split(), check=True)
        else:
            print(f"\n\nWARNING: {target_dir} already exists. Delete or move it to update files.")


def main():
    """Debloat benchmarks using LMCAS and test debloated binaries"""
    parser = argparse.ArgumentParser()
    group = parser.add_mutually_exclusive_group()
    group.add_argument("--list", action="store_true", help="List all benchmarks.")
    group.add_argument(
        "-b",
        dest="benchmark_regex",
        default=".*",
        help="Process benchmarks which match the given regex. If no regex is provided, all benchmarks will be processed",
    )
    parser.add_argument("--no-build", dest="no_build", action="store_true",
                        help="Disable benchmark building")
    parser.add_argument("--no-dry-run", dest="no_dry_run", action="store_true",
                        help=("Disable benchmark dry run to optimize and whole-program "
                              "compile without debloating"))
    parser.add_argument("--no-debloat", dest="no_debloat", action="store_true",
                        help="Disable benchmark debloating")
    parser.add_argument("--no-performance-tests", dest="no_perf", action="store_true",
                        help="Disable running performance tests on original/debloated binaries")
    parser.add_argument("--perf-test-target", dest="perf_test_target", choices=[ORIGINAL, DEBLOATED],
                        default=DEBLOATED, help=f"Target binaries for performance test, default {DEBLOATED}.")
    parser.add_argument("--no-save-binaries", dest="no_save_binaries", action="store_true",
                        help="Disable saving built/debloated binaries to repository")
    parser.add_argument("--tool-metrics-filename", dest="tool_metrics_filename", default="tool_metrics.csv",
                        help="Output file where debloating metrics are saved")
    parser.add_argument("--binary-metrics-filename", dest="binary_metrics_filename", default="binary_metrics.csv",
                        help="Output file where performance test metrics are saved")
    args = parser.parse_args()


    config = load_config()
    config_map = {key: value for key, value in config.items() if not key.startswith(".")}
    benchmark_names = [name for name in config_map.keys() if name.startswith(ALL_BENCHMARK_COMPLEXITIES)]

    if args.list:
        for benchmark_name in benchmark_names:
            print(benchmark_name)
        return

    # Pull LMCAS docker image
    cmd = f"docker pull {IMAGE_NAME}"
    print(cmd)
    subprocess.run(cmd.split(), check=True)

    copy_benchmarks_and_specs()

    re_benchmarks = re.compile(args.benchmark_regex)
    to_process = [benchmark_name for benchmark_name in benchmark_names if re_benchmarks.search(benchmark_name)]

    if not to_process:
        raise ValueError(f"No benchmarks found to match regex {args.benchmark_regex}")

    successes = []
    failures = []

    for benchmark_name in to_process:
        print(f"Processing benchmark: {benchmark_name}")
        try:
            process_benchmark(args, benchmark_name, config_map)
            successes.append(benchmark_name)
        except subprocess.CalledProcessError as error:
            print(f"\n\nERROR: Failed to process {benchmark_name}: {error}")
            failures.append(benchmark_name)


    tool_metrics.collect_metrics(output_csv_path=Path(args.tool_metrics_filename))
    binary_metrics.collect_metrics(output_csv_path=Path(args.binary_metrics_filename))
    print(f"\nSuccessfully processed benchmarks: {successes}\n")
    print(f"\nFailed to process benchmarks: {failures}\n")


if __name__ == "__main__":
    main()
