from enum import Enum
from pathlib import Path
from typing import Any, Dict
import yaml


SPEC_FILE = Path(__file__).absolute().parent / "binaries.yml"


class Arch(Enum):
    _32 = "32"
    _64 = "64"


ARCH_MARKER = "{ARCH_FLAGS}"
ARCH_FLAGS = {Arch._32: "-target i386-linux-elf", Arch._64: ""}
COMPILE_MARKER = "{COMPILE_FLAGS}"
COMPILE_FLAGS = "-O3 -fPIC -fPIE"
LINK_MARKER = "{LINK_FLAGS}"
LINK_FLAGS = "-pie"

CFI_COMPILE_FLAGS = " -flto -fsanitize=cfi -fsanitize-cfi-cross-dso -fvisibility=default -fno-sanitize-trap=all "

def make_variables(arch: Arch, cfi: bool) -> Dict[str, str]:
    return {
        ARCH_MARKER: ARCH_FLAGS[arch],
        COMPILE_MARKER: COMPILE_FLAGS + (CFI_COMPILE_FLAGS if cfi else ""),
        LINK_MARKER: LINK_FLAGS,
    }


def expand_variables(benchmark: Dict[str, Any], arch: Arch, vars: Dict[str, str]):
    "Used to interpolate the {COMPILE_FLAGS}, etc strings in the yml file."

    result = benchmark.copy()

    def interpolate(string):
        for name, value in vars.items():
            string = string.replace(name, value)
        return string

    def expand_dict(key):
        result[key] = {k: interpolate(v) for k, v in result[key].items()}

    def expand_list(key):
        result[key] = [interpolate(s) for s in result[key]]

    def apply_arch(key):
        if arch.value in benchmark[key]:
            result[key] = benchmark[key][arch.value]

    apply_arch("packages")
    apply_arch("pre-build")

    expand_dict("env")
    expand_list("pre-build")
    expand_list("build")
    return result


def benchmark_binaries() -> Dict[str, Dict[str, Any]]:
    with open(SPEC_FILE) as f:
        spec = yaml.safe_load(f)
    return {
        benchmark: info
        for benchmark, info in spec.items()
        if not benchmark.startswith(".")
    }
