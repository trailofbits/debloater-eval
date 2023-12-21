"""Print info on crashes/errors for a differ run"""
import argparse
import yaml
from pathlib import Path
from typing import Dict

def get_yaml(path: Path) -> Dict:
    with open(path, 'r') as f:
        return yaml.load(f.read(), Loader=yaml.Loader)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("result_dir", help="Directory with results from a differ run", type=Path)
    args = parser.parse_args()
    result_dir = args.result_dir
    if not result_dir.is_dir():
        print("Didn't provide valid directory")
        return
    crashes = {}
    errors = {}
    for path in result_dir.iterdir():
        if path.is_dir():
            continue
        if "crash" in str(path):
            data = get_yaml(path)
            details = data['details']
            crashes[details] = crashes.get(details, 0) + 1
        elif "error" in str(path):
            data = get_yaml(path)
            for result in data["results"]:
                if result['status'] == "error":
                    error_str = f"{result['comparator']}: {result['details']}"
                    errors[error_str] = crashes.get(error_str, 0) + 1
    print(f"Digest for \"{result_dir}\"")
    print(f"Crashes:")
    for crash, count in crashes.items():
        print(f"\t{count}: {crash}")
    print(f"Errors:")
    for error, count in errors.items():
        print(f"\t{count}: {error}")

if __name__ == "__main__":
    main()