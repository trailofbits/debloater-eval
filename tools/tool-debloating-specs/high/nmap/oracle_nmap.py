from chisel_oracle import OracleHelper, finish, terminate
import os
import tempfile
import unittest
import shutil
import subprocess
from contextlib import contextmanager
import shlex

binary = "[no binary specified]"
oracle = OracleHelper(__name__.replace("oracle_", ""))

def train_run(testcase, cmd):
    finish(oracle.check_process(
        testcase,
        str(binary) + " " + cmd,
        redactors=[
            r"\d\d\d\d-\d\d-\d\d \d\d:\d\d", # Datetime
            r"\d*\.\d+ seconds", # runtime in seconds
            r"\d*\.\d+s latency", # latency
        ]
    ))
    oracle.check_directory(testcase, ".", redactors=[
        r"\w+ \w+ \d{1,2} \d\d:\d\d:\d\d \d\d\d\d", # Datetime
        r"start=\"\d+\"", # time information from report
        r"start=\"\d+\"",
        r"starttime=\"\d+\"",
        r"endtime=\"\d+\"",
        r"srtt=\"\d+\"",
        r"rttvar=\"\d+\"",
        r"elapsed=\"\d*\.\d*\"",
        r"time=\"\d+\"",
        r"\d*\.\d+ seconds",
        r"\d*\.\d+s latency", # latency        
    ])


@contextmanager
def tcp(testcase, port, content):
    cm = oracle.check_process(
        testcase,
        "nc -l {}".format(port),
        stdin=content,
        shutdown=terminate
    )
    try:
        yield cm.__enter__()
    finally:
        cm.__exit__(None, None, None)

@contextmanager
def http(testcase, port, directory):
    cm = oracle.check_process(
        testcase,
        "python3 -m http.server {}".format(port),
        shutdown=terminate
    )
    try:
        yield cm.__enter__()
    finally:
        cm.__exit__(None, None, None)

class Oracle(unittest.TestCase):
    def setUp(self):
        self.dir = tempfile.mkdtemp()
        self.prior_dir = os.getcwd()
        self.maxDiff = None
        os.chdir(self.dir)
        shutil.copytree("/input_files/nmap-serve", "serve")

    def tearDown(self):
        os.chdir(self.prior_dir)
        shutil.rmtree(self.dir)

    def test_tcp_port_scan(self):
        with tcp(self, 8080, "hello world\n"):
            train_run(self, "-sT 127.0.0.1")

    def test_tcp_port_scan_range(self):
        with tcp(self, 8080, "hello world\n"):
            with tcp(self, 8081, "you should not see this\n"):
                with tcp(self, 7080, "you should see this\n"):
                    train_run(self, "-sT -p1-7080,8080 127.0.0.1")

    def test_service_scan(self):
        with http(self, 8080, "serve"):
            train_run(self, "-sT -sV 127.0.0.1")

    def test_service_scan_output(self):
        with http(self, 8080, "serve"):
            for output_flag in ["-oG", "-oN", "-oX"]:
                train_run(self, "-sT -sV {} report 127.0.0.1".format(output_flag))
