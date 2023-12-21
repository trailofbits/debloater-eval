"""Validate campaigns 

Valid campaign: all crash/error reports are for true-positive semantic differences
"""
import argparse
from pathlib import Path
import yaml
import sys
from typing import Dict, List
import logging


def get_yaml(path: Path) -> Dict:
    # TODO deduplicate this function in other scripts
    try:
        with open(path, 'r') as f:
            return yaml.load(f.read(), Loader=yaml.Loader)
    except:
        logging.warning(f"Failed loading yaml of {path}\n")

def comparator_auto_valid(data: Dict) -> bool:
    """Determine if comparator difference is automatically valid"""
    comparator = data['comparator']
    details = data['details']
    status = data['status']
    if status != "error":
        logging.warning(f"Status not error: {comparator} {status}")
        return False
    if comparator == "exit_code":
        return "exit codes do not match" in details
    elif comparator == "__executor__":
        return "trace was expected to fail but did not" in details
    elif comparator == "concurrent_script[exit_code]":
        return "concurrent hook script exit code does not match" in details
    # remaining comparators require manual validation
    elif comparator == "file":
        return False
    elif comparator == "stderr":
        # TODO autodetect gtirb trap set (this is a true positive)
        return False
    elif comparator == "stdout":
        return False
    elif comparator == "teardown_script[exit_code]":
        return False
    elif comparator == "teardown_script[output]":
        return False
    elif comparator == "pcap":
        return False
    elif comparator == "concurrent_script[output]":
        return False
    elif comparator == "file[owner]":
        return False
    else:
        logging.warning(f"Unsupported comparator: {comparator} {details}")

def validate_report(report_path: Path) -> bool:
    report = get_yaml(report_path)
    for comparator in report['results']:
        # if one comparator has true positive difference, then report is valid
        if comparator_auto_valid(comparator):
            return True
    return False

def validate_crash(report_path: Path) -> bool:
    report = get_yaml(report_path)
    details = report['details']
    name = str(report_path.name)
    # Logging original crashes, although we decided to allow for now
    if name.startswith("crash-__original__"):
        logging.warning(f"Original crash: {report_path}")
    if 'process exit from signal SIGSEGV' in details:
        return True
    elif 'unexpected exit code' in details:
        return True
    elif 'file does not exist' in details:
        return True
    elif 'Process was terminated because of an unexpected timeout' in details:
        return True
    elif 'process exit from signal SIGABRT' in details:
        return True
    elif 'file content does not meet similarity requirement' in details:
        # requires manual review
        return False
    logging.warning(f"Unsupported crash type: {details}")
    return False

def validate_campaign(report_dir: Path) -> List:
    requires_review = []
    for path in report_dir.iterdir():
        if path.is_dir():
            continue
        name = str(path.name)
        if name.startswith("crash-"):
            if not validate_crash(path):
                requires_review.append(path)
        elif name.startswith("report-"):
            if not validate_report(path):
                requires_review.append(path)
        else:
            logging.warning(f"ERROR not crash or report: {path}")
    return requires_review

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("reports_dir", help="Directory storing reports from differ run", type=Path)
    args = parser.parse_args()
    reports_dir = args.reports_dir
    # validate each campaign report
    for path in reports_dir.iterdir():
        if not path.is_dir():
            continue
        requires_review = validate_campaign(path)
        if len(requires_review) == 0:
            print(f"VALIDATED: {path}")
        else:
            print(f"NOT VALIDATED: {path}")
            for report in requires_review:
                logging.warning(f"REVIEW: {path} {report}")

if __name__ == "__main__":
    main()