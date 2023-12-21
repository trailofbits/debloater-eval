# List all the ubuntu 20 packages needed by a benchmark

import yaml
import sys

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 install-packages.py [benchmark]")
        exit(1)

    with open("build-binaries/binaries.yml", "r") as bin_file:
        data = yaml.safe_load(bin_file)

    benchmark = data[sys.argv[1]]
    if type(benchmark["packages"]) is list:
        package_list = benchmark["packages"]
    else:
        package_list = benchmark["packages"]["64"]

    pkgs = (
        pkg for pkg in package_list
        if not pkg.endswith(":i386")
    )
    for pkg in pkgs:
        print(f"{pkg}", end=" ")
    exit(0)
