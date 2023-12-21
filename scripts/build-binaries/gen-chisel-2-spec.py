#!/usr/bin/env python3
import argparse
import sys
from typing import Any, Dict, List, Optional

import yaml

from benchmark_binaries import (
    COMPILE_MARKER,
    LINK_MARKER,
    SPEC_FILE,
    Arch,
    benchmark_binaries,
    expand_variables,
    make_variables,
)
from chisel.source.buildsystem import IDEAL_BUILD_FLAGS
from chisel.source.targetspec import SourceTargetSpec
from chisel.common.targetspec import Command


def _cmd(cmds: List[str], env=None) -> Optional[Command]:
    if len(cmds) == 0:
        return None
    if len(cmds) > 1:
        result = Command(command="bash", args=["-e", "-c", ";".join(cmds)])
    else:
        result = Command.from_commandline(cmds[0])
    if env:
        result.env.update(env)
    return result


def _sanitized_vars(arch: Arch):
    result = make_variables(arch)

    def _add_flags(key: str, flags: List[str]):
        result[key] += " " + " ".join(flags)

    sanitizer_flags = IDEAL_BUILD_FLAGS.sanitizer_flags
    _add_flags(COMPILE_MARKER, sanitizer_flags + IDEAL_BUILD_FLAGS.warning_flags)
    _add_flags(LINK_MARKER, sanitizer_flags)
    return result


def spec_from_benchmark(benchmark_spec: Dict[str, Any], oracle_cmd: str) -> SourceTargetSpec:
    c_source_exts = [".c", ".h"]
    arch = Arch._64
    benchmark = expand_variables(benchmark_spec, arch, make_variables(arch))
    benchmark_sanitized = expand_variables(benchmark_spec, arch, _sanitized_vars(arch))
    sanitized_env = benchmark_sanitized["env"]
    return SourceTargetSpec(
        sources=["**/*" + ext for ext in c_source_exts],
        assets=["*"],
        prepare=_cmd(benchmark["pre-build"]),
        sanitized_prepare=_cmd(benchmark_sanitized["pre-build"], env=sanitized_env),
        oracle=Command(command=oracle_cmd),
        build=_cmd(benchmark["build"]),
        sanitized_build=_cmd(benchmark_sanitized["build"], env=sanitized_env),
        env=benchmark["env"],
    )


if __name__ == "__main__":
    benchmarks = benchmark_binaries()

    parser = argparse.ArgumentParser(description="Generate Chisel spec.")
    parser.add_argument(
        "name", choices=benchmarks.keys(), help=f"Entry from {SPEC_FILE}"
    )
    parser.add_argument(
        "oracle_cmd", type=str, help="The oracle cmd."
    )
    args = parser.parse_args()
    spec = spec_from_benchmark(benchmarks[args.name], args.oracle_cmd)
    spec_dict = spec.dict(exclude_defaults=True)
    yaml.dump(spec_dict, sys.stdout)
