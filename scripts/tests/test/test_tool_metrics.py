"""Test metrics"""

import shlex
import subprocess

from debloater_eval.metrics import Metrics


def test_metrics(tmpdir):
    """Test tool metrics"""
    metrics = Metrics()
    cmd = "sleep 1"
    binary_name = "test"

    cmds, _ = metrics.get_commands_with_metrics(cmd, binary_name)
    for cmd in cmds:
        subprocess.run(shlex.split(cmd), check=True)
    output_csv_path = tmpdir / "metrics.csv"
    metrics = metrics.collect_metrics(output_csv_path)

    assert binary_name in metrics
    assert round(float(metrics[binary_name]["real_time"]), 0) == 1
    assert int(metrics[binary_name]["exit_status"]) == 0
