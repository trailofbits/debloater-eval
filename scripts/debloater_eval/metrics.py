"""Collect runtime and memory usage"""

import csv
from pathlib import Path
from typing import Dict, List, Optional, Tuple

TIME_FORMAT = {
    "real_time": "%e",
    "cpu_time_kernel": "%S",
    "cpu_time_user": "%U",
    "maximum_resident_set_size": "%M",
    "exit_status": "%x",
}

BINARY_NAME = "binary_name"
TIMEOUT = 86400

class Metrics:
    """Collect metrics for running command"""

    def __init__(self, time_command: str = "/usr/bin/time",
                 timeout_command: str = "timeout",
                 output_dir: Path = Path("/tmp/metrics")):
        self.time_command = time_command
        self.timeout_command = timeout_command
        self.output_dir = output_dir
        self.setup_command = f"mkdir -p {self.output_dir}"
        self.metrics_paths = {}

    def get_commands_with_metrics(self, command: str, binary_name: str) -> Tuple[List[str], Path]:
        """Get commands to collect metrics while running given command"""
        metrics_path = self.output_dir / f"metrics_{binary_name}.csv"
        self.metrics_paths[binary_name] = metrics_path
        cmds = [self.setup_command]
        cmds.append(f"{self.time_command} -q -f {','.join(TIME_FORMAT.values())} -o {metrics_path} {self.timeout_command} {TIMEOUT} {command}")
        return cmds, metrics_path

    def collect_metrics(self, output_csv_path: Optional[Path]) -> Dict[str, Dict[str, str]]:
        """Collect and save metrics for all processed binaries"""
        all_metrics = {}
        for binary_name, metrics_path in self.metrics_paths.items():
            if not metrics_path.exists():
                raise FileNotFoundError(f"Metrics file {metrics_path} for binary {binary_name} not found; it must exist on host to collect metrics")
            with metrics_path.open("r", encoding="utf-8") as file:
                reader = csv.reader(file)
                all_metrics[binary_name] = dict(zip(TIME_FORMAT.keys(), next(reader)))

        if output_csv_path:
            # Dump metrics into single CSV file
            with output_csv_path.open("w", encoding="utf-8") as file:
                writer = csv.DictWriter(file, fieldnames=[BINARY_NAME] + list(TIME_FORMAT.keys()))
                writer.writeheader()
                for binary_name, binary_metrics in all_metrics.items():
                    writer.writerow({**{BINARY_NAME: binary_name}, **binary_metrics})

        return all_metrics
