"""Print JSON fields as yaml snippets to help make differ yaml files"""
import argparse
from batch_gsa import BatchConfig
from typing import Dict
import json
from yaml import dump
from pathlib import Path

def format_yaml_data(batch_config: BatchConfig, binary_prefix: Path) -> Dict:
    data = []
    for binary in batch_config.binaries:
        yaml_data = binary.to_yaml(batch_config.binary_base_path, binary_prefix)
        data.append((binary.name, dump(yaml_data)))
    data.sort(key= lambda x: x[0])
    print("************************")
    for bin in data:
        print(bin[0])
        print(bin[1])
        print("************************")

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("batch_json", help="JSON file which specifies batch")
    parser.add_argument("binary_prefix", help="prefix to add to binary paths", type=Path)
    args = parser.parse_args()
    batch_json = args.batch_json
    binary_prefix = args.binary_prefix
    with open(batch_json, 'r') as f:
        batch_config_dict = json.loads(f.read())
    batch_config = BatchConfig.from_dict(batch_config_dict)
    format_yaml_data(batch_config, binary_prefix)





if __name__ == "__main__":
    main()