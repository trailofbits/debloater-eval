"""Build CSV of file size and dynamic library count for binaries"""
import argparse
import json
from batch_gsa import BatchConfig
from pathlib import Path
import os
import subprocess
import logging

logging.basicConfig(level=logging.DEBUG)

KILOBYTE=1024

def filesize(path: Path) -> int:
    """Get filesize of file in kilobytes, rounded to one decimal place"""
    stats = os.stat(path)
    return round(stats.st_size/KILOBYTE, 1)

def run_ldd_standard(path: Path, ld_path: Path) -> subprocess.CompletedProcess:
    """Run ldd"""
    return subprocess.run(["ldd", path], capture_output=True, check=True, env={'LD_LIBRARY_PATH':str(ld_path)})

def run_ldd_docker(path: Path, image_name: str, ld_path: Path) -> subprocess.CompletedProcess:
    """Run ldd in a docker container

    This is to handle binaries with additional dependencies, such as:
        - alpine to handle ones linked with musl"""
    dirname = os.path.dirname(path)
    filename = os.path.basename(path)
    command = ["docker",
        "run",
        "-it",
        "-v",
        f"{dirname}:/test:ro",
        "-v"
        f"{ld_path}:/morelibs:ro",
        "-w",
        "/test",
        "-e",
        'LD_LIBRARY_PATH=/morelibs',
        image_name,
        "ldd",
        filename]
    logging.debug(f"docker command: {' '.join(command)}")
    return subprocess.run(command, capture_output=True, check=True)

def get_lib_count(proc: subprocess.CompletedProcess) -> int:
    """Get library count from stdout of completed ldd command"""
    output_str = proc.stdout.decode("utf-8").strip()
    libs = output_str.split("\n")
    for lib in libs:
        assert ".so" in lib, f"Line isn't library: {lib}"
        assert "not found" not in lib and "No such" not in lib, f"Library not found: {lib}"
    return len(libs)
    

def dynamic_libs(binary_name: str, name: str, path: Path, ld_path: Path) -> int | str:
    """Count dynamic libraries"""
    check_static_proc = subprocess.run(['file', path], capture_output=True, check=True)
    output_static_str = check_static_proc.stdout.decode("utf-8").strip()
    if ", statically linked," in output_static_str:
        logging.info(f"Statically linked: {binary_name} {name}")
        return 0
    lib_count = None
    try:
        proc = run_ldd_standard(path, ld_path)
        lib_count = get_lib_count(proc)
    except Exception as e:
        logging.debug(f"Standard failed: {binary_name} {name} with error: {e}")
        for docker_img in ["ubuntu-stats:latest", "buster-stats:latest", "alpine"]:
            try:
                logging.debug(f"Trying docker image: {docker_img}")
                proc = run_ldd_docker(path, docker_img, ld_path)
                lib_count = get_lib_count(proc)
            except Exception as e:
                logging.debug(f"Image {docker_img} failed: {binary_name} {name} with error: {e}")
            else:
                break
    if lib_count is not None:
        return lib_count
    else:
        return "ERROR"

def get_row(binary_name: str, name: str, path: Path, ld_path: Path) -> str:
    """Build row string"""
    row = ""
    try:
        row = f"{binary_name},{name},{filesize(path)},{dynamic_libs(binary_name, name, path, ld_path)}"
    except Exception as e:
        logging.warning(f"Failed: {binary_name} {name} with error {e}")
    return row

def print_row(binary_name: str, name: str, path: Path, ld_path: Path) -> str:
    """Print row if successful"""
    row = get_row(binary_name, name, path, ld_path)
    if len(row) > 0:
        print(row)

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("batch_json", help="JSON file which specifies batch")
    args = parser.parse_args()
    batch_json = args.batch_json
    with open(batch_json, 'r') as f:
        batch_config_dict = json.loads(f.read())
    batch_config = BatchConfig.from_dict(batch_config_dict)
    print("source,variant,size_kb,dynamic_libs")
    for binary in batch_config.binaries:
        orig_path = binary.original_path
        # pick up any libraries in directory of original binary
        ld_path = Path(orig_path).parent
        print_row(binary.name, "original", orig_path, ld_path)
        for name, path in binary.variants.items():
            print_row(binary.name, name, path, ld_path)

if __name__ == "__main__":
    main()
