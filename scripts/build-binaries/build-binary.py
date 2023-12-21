import shlex
import subprocess
from pathlib import Path
from contextlib import contextmanager
import argparse
import re
from typing import Any, Dict

from benchmark_binaries import (
    Arch,
    benchmark_binaries,
    expand_variables,
    make_variables,
)


IMAGE_NAME="debloat-eval-binaries"


@contextmanager
def run_container(work_dir, env_vars):
    CONTAINER_NAME="debloat-eval-binaries"
    env_args = [
        f"--env {name}=\"{value}\"" for name, value in env_vars.items()
    ]
    cmd = (
        f"docker run -d --network=host --name {CONTAINER_NAME} "
        f"-w {work_dir} {' '.join(env_args)} "
        f"{IMAGE_NAME} tail -f /dev/null"
    )
    cmd = shlex.split(cmd)
    print(cmd)
    subprocess.run(
        cmd,
        check=True
    )
    try:
        yield CONTAINER_NAME
    finally:
        pass
#        subprocess.run(
#            ["docker", "container", "rm", "-f", CONTAINER_NAME],
#            stdout=subprocess.PIPE,
#            stderr=subprocess.PIPE
#        )


def dexec(container, cmd):
    subprocess.run(
        shlex.split(f"docker exec {container} {cmd}"),
        check=True
    )


def build_binary(benchmark_name, benchmark: Dict[str, Any], arch: Arch, cfi: bool):
    working_dir = (
        Path('/usr/src/benchmarks') / benchmark_name /
        'source' / benchmark["source-dir"]
    )

    with run_container(working_dir, benchmark["env"]) as container:
        if packages := benchmark["packages"]:
            dexec(container, "apt-get update -y")
            for package in packages:
                dexec(container, f"apt-get install -y {package}")
        for cmd in benchmark.get("init", []):
            print(cmd)
            dexec(container, cmd)
        for cmd in benchmark["pre-build"]:
            print(cmd)
            dexec(container, cmd)
        for cmd in benchmark['build']:
            dexec(container, cmd)
        output_dir = Path("../benchmarks") / benchmark_name / "binaries" / (arch.value + ("-cfi" if cfi else ""))
        output_dir.mkdir(parents=True, exist_ok=True)
        for binary in benchmark["binaries"]:
            print(f"Copying {binary}")
            binary_location = working_dir / binary
            subprocess.run(
                f"docker cp {container}:{binary_location} {output_dir}".split(),
                check=True
            )


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description = "Build binaries to be used by evaluation."
    )
    parser.add_argument(
        "--arch",
        default=Arch._64,
        type=Arch,
        dest="arch",
        help=(
            f"The architecture of the binary to be built.  Default={Arch._64.value},"
            f" the other possible value is {Arch._32.value}."
        )
    )
    parser.add_argument(
        "--cfi",
        action="store_true",
        help=("Compile with CFI")
    )
    group = parser.add_mutually_exclusive_group()
    group.add_argument(
        "--list",
        action="store_true",
        help="List all benchmarks."
    )
    group.add_argument(
        "-b",
        dest="benchmark",
        metavar="[BENCHMARK PATTERN]",
        help="Build benchmarks which match the given regex."
    )
    args = parser.parse_args()

    benchmarks = benchmark_binaries()
    if args.list:
        for benchmark in benchmarks.keys():
            print(benchmark)
    else:
        subprocess.run(
            (
                f"docker build -t {IMAGE_NAME} -f Dockerfile --network=host "
                ".."
            ).split(),
            check=True
        )
        to_build = [
            key for key in benchmarks.keys() if re.match(args.benchmark, key)
        ]
        print(f"Building: {to_build}")
        arch = args.arch
        vars = make_variables(arch, args.cfi)
        for name in to_build:
            try:
                build_binary(name, expand_variables(benchmarks[name], arch, vars), arch, args.cfi)
            except Exception as e:
                print(f"\n\nERROR: Failed to build {name}")
                raise e
