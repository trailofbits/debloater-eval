"""Count number of error/crash reports per binary in each campaign"""
import argparse
from pathlib import Path
import yaml
import json
from typing import Dict
import logging


def get_yaml(path: Path) -> Dict:
    # TODO deduplicate this function in other scripts
    try:
        with open(path, 'r') as f:
            return yaml.load(f.read(), Loader=yaml.Loader)
    except:
        logging.warning(f"Failed loading yaml of {path}\n")

def main():
    parser = argparse.ArgumentParser()
    # make sure reports directory and the yaml pattern match (e.g. both are aggressive)
    parser.add_argument("reports_dir", help="Directory storing reports from differ run", type=Path)
    parser.add_argument("yaml_pat")
    args = parser.parse_args()
    reports_dir = args.reports_dir
    yaml_pat = args.yaml_pat
    # validate each campaign report
    results = {}
    for file in Path(".").rglob(yaml_pat):
        filepath = Path(file)
        data = get_yaml(filepath)
        if data is None:
            continue
        binary_fails = {"__original__": 0}
        for k in data['debloaters'].keys():
            binary_fails[k] = 0
        campaign = data['name']
        campaign_reports = reports_dir / campaign
        if not campaign_reports.exists():
            logging.warning(f"Skipping campaign: {campaign_reports}")
            continue
        # map each crash/error report to a binary
        for path in campaign_reports.iterdir():
            if path.is_dir():
                continue
            report_name = str(path.name)
            if not "crash" in report_name and not "error" in report_name:
                logging.warning(f"Skipping report: {path}")
                continue
            report_split = report_name.split("-")
            # try name separated by hyphen first
            binary = "-".join(report_split[1:3])
            if binary in binary_fails:
                binary_fails[binary] += 1
                continue
            # try name without hyphen
            binary = report_split[1]
            if binary in binary_fails:
                binary_fails[binary] += 1
                continue
            logging.warning(f"Skipping report: {path}")
        results[f"{campaign}-{reports_dir}"] = binary_fails
    print(json.dumps(results, indent=1))

            

if __name__ == "__main__":
    main()