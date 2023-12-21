"""Diff the content-based comparators of a differ report

Note: this script only content diffs between the original and debloated.
Since differ can diff file content against a file that is not the original, this script
just reports differ output for file similarity.
"""
import argparse
from pathlib import Path
from typing import Dict
import logging
import os
from validate_campaigns import comparator_auto_valid, validate_crash, get_yaml

KILOBYTE=1024

def filesize(path: Path) -> int:
    """Get filesize of file in kilobytes, rounded to three decimal places"""
    stats = os.stat(path)
    return round(stats.st_size/KILOBYTE, 3)

def diff_contents(filename: Path, trace_dir: Path):
    """Print the contents of the file in the original and debloated trace dirs"""
    orig_trace_dir = trace_dir.parent / "__original__"
    orig_file = orig_trace_dir / filename
    debloat_file = trace_dir / filename
    print("<<<")
    with open(orig_file, 'rb') as f:
        contents = f.read()
        print(contents)
    print(">>>")
    with open(debloat_file, 'rb') as f:
        contents = f.read()
        print(contents)

def diff_filesize(filename: Path, trace_dir: Path):
    """Print the sizes of the file in the original and debloated trace dirs"""
    orig_trace_dir = trace_dir.parent / "__original__"
    orig_file = orig_trace_dir / filename
    debloat_file = trace_dir / filename
    print("<<<")
    print(f"{filesize(orig_file)} KB")
    print(">>>")
    print(f"{filesize(debloat_file)} KB")

def diff_comparator(data: Dict, trace_dir: Path):
    """Diff each comparator in a report, against the original
    
    Comparators which can be auto-validated are skipped
    """
    comparator = data['comparator']
    details = data['details']

    if comparator_auto_valid(data):
        print(f"comparator {comparator}: DIFFERS")
    elif comparator == "file":
        print(f"comparator: {comparator}")
        if "file exists:" in details:
            print(f"comparator: {comparator} Unexpected file exists")
            return
        if "file does not exist:" in details:
            print(f"comparator: {comparator} Unexpected file missing")
            return
        # file similarity
        file_similarity = details.split('similarity requirement: ')[1]
        print(f"comparator: {comparator}: {file_similarity}")
    elif comparator == "stderr":
        print(f"comparator: {comparator}")
        diff_contents("__differ-stderr.bin", trace_dir)
    elif comparator == "stdout":
        print(f"comparator: {comparator}")
        diff_contents("__differ-stdout.bin", trace_dir)
    elif comparator == "teardown_script[exit_code]":
        print(f"comparator: {comparator}")
        diff_contents("__differ-teardown-output.bin", trace_dir)
    elif comparator == "teardown_script[output]":
        print(f"comparator: {comparator}")
        diff_contents("__differ-teardown-output.bin", trace_dir)
    elif comparator == "pcap":
        print(f"comparator: {comparator}")
        diff_filesize("capture.pcap", trace_dir)
    elif comparator == "concurrent_script[output]":
        print(f"comparator: {comparator}")
        diff_contents("__differ-concurrent-output.bin", trace_dir)
    elif comparator == "file[owner]":
        print(f"comparator: {comparator}")
        print(f"details: {details}")
        print(f"look at file in trace: {trace_dir}")
    else:
        logging.warning(f"Unsupported comparator: {comparator} {details}")

def diff_report(report: Path):
    """Diff comparators in an error report"""
    data = get_yaml(report)
    if data is None:
        return
    trace_dir = Path(data['trace_directory'])
    for comparator in data['results']:
        diff_comparator(comparator, trace_dir)

def diff_crash(report: Path):
    """Diff details in a crash report"""
    data = get_yaml(report)
    if data is None:
        return
    trace_dir = Path(data['trace_directory'])
    details = data['details']
    if validate_crash(report):
        print(f"crash DIFFERS")
    elif 'file content does not meet similarity requirement' in details:
        file_similarity = details.split('similarity requirement: ')[1]
        print(f"file similarity: {file_similarity}")
    else:
        logging.warning(f"Unsupported crash details: {report} {details}")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("reports", help="Reports for a differ crash/error", type=Path, nargs="+")
    args = parser.parse_args()
    reports = args.reports
    for report in reports:
        print(f"Diffing {report}\n<<< original >>> debloated")
        name = str(report.name)
        if name.startswith("crash-"):
            diff_crash(report)
        elif name.startswith("report-"):
            diff_report(report)
        else:
            logging.warning(f"ERROR not crash or report: {report}")


if __name__ == "__main__":
    main()