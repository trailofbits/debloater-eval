"""Check that all binaries in yamls matching pattern have all dynamic libraries"""
import argparse
import yaml
from pathlib import Path
from typing import Dict
import os
import subprocess
import logging

def get_yaml(path: Path) -> Dict:
    try:
        with open(path, 'r') as f:
            return yaml.load(f.read(), Loader=yaml.Loader)
    except:
        logging.warning(f"Failed loading yaml of {path}\n")

def normalize_path(path: str) -> str:
    # assumes paths in files are prepended with ../..
    # and that ../.. is the directory this script is being run in
    return str(os.path.relpath(path, "../.."))

def ldd_works(path: Path) -> bool:
    """Run ldd"""
    # check if statically linked
    check_static_proc = subprocess.run(['file', path], capture_output=True, check=True)
    output_static_str = check_static_proc.stdout.decode("utf-8").strip()
    if ", statically linked," in output_static_str:
        return True
    proc = subprocess.run(["ldd", path], capture_output=True)
    # check that ldd runs without erroring
    if proc.returncode != 0:
        logging.debug(f"{path}: ldd fails\n")
        return False
    # this part is adapted from within get_lib_count in collect-stats.py
    # check that all libraries are found
    output_str = proc.stdout.decode("utf-8").strip()
    libs = output_str.split("\n")
    missing = []
    for lib in libs:
        if "not found"  in lib or "No such"  in lib:
            missing.append(lib)
    for missing_lib in missing:
        logging.debug(f"{path}: missing library \"{missing_lib.strip()}\"")
    return len(missing) == 0

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("yaml_pat", help="yaml filename to recursively find")
    parser.add_argument("-v", "--verbose", help="verbose", action="store_true")
    args = parser.parse_args()
    yaml_pat = args.yaml_pat
    verbose = args.verbose
    log_level = logging.WARN
    if verbose:
        log_level = logging.DEBUG
    logging.basicConfig(level=log_level)
    binaries = set()
    for file in Path(".").rglob(yaml_pat):
        filepath = Path(file)
        data = get_yaml(filepath)
        if data:
            binaries.add(normalize_path(data['original']))
            for _, path in data['debloaters'].items():
                binaries.add(normalize_path(path))
    for binary in binaries:
        if ldd_works(binary):
            print(f"works: {binary}")
        else:
            print(f"fails: {binary}")
        



if __name__ == "__main__":
    main()