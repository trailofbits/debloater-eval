import subprocess
import argparse
import json
from pathlib import Path
import os
from typing import Dict, List, Self
from dataclasses import dataclass
import sys
from rich.progress import (
    MofNCompleteColumn,
    Progress,
    SpinnerColumn,
    TextColumn,
    TimeElapsedColumn,
)
from rich.console import Console
import logging

logger = logging.Logger('logger')

logger.setLevel(os.getenv("GSA_LOG_LEVEL", "INFO"))

"""
JSON format

{
    "batch_meta": {
        "binary_base_path": "BASE_PATH" # absolute path
        "results_path": "RESULTS_PATH   # absolute path
    },
    "binaries": {
        "BINARY_NAME": {
            "original_path": "ORIGINAL_PATH", # relative to binary_base_path
            "variants":{
                "VARIANT_NAME": "VARIANT_PATH", # relative to binary_base_path
                ...
            }
        },
        ...
    }
}
"""

@dataclass
class BinaryConfig:
    name: str
    original_path: Path
    variants: Dict[str, Path]

    def from_dict(name: str, base_path: Path, dict: Dict) -> Self:
        original_sub_path = Path(dict['original_path'])
        original_path = base_path / original_sub_path
        assert original_path.exists(), f"Original file doesn't exist: {original_path}"
        variants = {}
        for variant_name, variant_sub_path in dict['variants'].items():
            assert variant_name in variant_sub_path, f"Possible wrong name:path mapping detected: {variant_name} and {variant_sub_path}"
            variant_full_path = base_path / variant_sub_path
            assert variant_full_path.exists(), f"Variant file doesn't exist: {variant_full_path}"
            variants[variant_name] = variant_full_path
        return BinaryConfig(name, original_path, variants)

    def to_yaml(self, base_path: Path, bin_prefix: Path) -> Dict:
        original =  str(bin_prefix / self.original_path.relative_to(base_path))
        debloaters =  {k: str(bin_prefix / v.relative_to(base_path)) for k,v in self.variants.items()}
        dict  = {
            "original":original,
            "debloaters": debloaters
        }
        return dict

@dataclass
class BatchConfig:
    binary_base_path: Path
    results_path: Path
    binaries: List[BinaryConfig]
    
    def from_dict(dict: Dict) -> Self:
        # expand user for this paths because they may be absolute
        binary_base_path = Path(os.path.expanduser(dict['batch_meta']['binary_base_path']))
        results_path = Path(os.path.expanduser(dict['batch_meta']['results_path']))
        assert binary_base_path.is_absolute()
        assert results_path.is_absolute()
        binaries = []
        for binary_name, binary_contents in dict['binaries'].items():
            binaries.append(BinaryConfig.from_dict(binary_name, binary_base_path, binary_contents))
        return BatchConfig(binary_base_path, results_path, binaries)

def run_binary(binary_config: BinaryConfig, working_directory: Path):
    GSA_PY_PATH = os.environ["GSA_PY_PATH"]
    original_name = binary_config.name
    original_path = binary_config.original_path
    cmd = ["python",
           GSA_PY_PATH,
           "--output_metrics",
           "--output_simple",
           "--result_folder_name",
           str(original_name),
           str(original_path),
           "--variants"]
    for variant_name, variant_path in binary_config.variants.items():
        cmd.append(f"{variant_name}={variant_path}")
    logger.debug(" ".join(cmd))
    subprocess.run(cmd, check=True, cwd=working_directory)

def create_progress():
    console = Console(log_path=False, file=sys.stderr)
    progress = Progress(SpinnerColumn(), 
                  *Progress.get_default_columns(),
                  TimeElapsedColumn(),
                  MofNCompleteColumn(),
                  TextColumn("{task.fields[binary]}"),
                  console=console)
    return progress

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("batch_json", help="JSON file which specifies batch")
    args = parser.parse_args()
    batch_json = args.batch_json
    with open(batch_json, 'r') as f:
        batch_config_dict = json.loads(f.read())
    batch_config = BatchConfig.from_dict(batch_config_dict)
    os.mkdir(batch_config.results_path)
    with create_progress() as progress:
        task = progress.add_task("Evaluating binaries", total=len(batch_config.binaries), binary="")
        for binary in batch_config.binaries:
            run_binary(binary, batch_config.results_path)
            progress.update(task, advance=1, binary=f"{binary.name}: {len(binary.variants)} variants")

if __name__ == "__main__":
    main()

