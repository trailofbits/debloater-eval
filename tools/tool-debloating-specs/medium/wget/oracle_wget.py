from chisel_oracle import OracleHelper, finish, terminate
import tempfile
import os
import shutil
import unittest
import socket
from contextlib import contextmanager

binary = "[no binary specified]"
oracle = OracleHelper(__name__.replace("oracle_", ""))


HOST = "rs-chisel-wget-server-vm.grammatech.com"


class Oracle(unittest.TestCase):
    def setUp(self):
        self.prior_dir = os.getcwd()
        self.dir = tempfile.mkdtemp()
        self.maxDiff = None
        self.redactors = [
            r"\d+\.\d+ MB/s", # Transfer rate
            r"\d+ [KMG]B\/s",
            r"\d\d\d\d-\d\d-\d\d \d\d:\d\d:\d\d", # Transfer datetime
            r"\d+\.?\d*[KM]=\d+s", # Transfer rate and time
            r"(\d{1,3}\.){3}\d{1,3}", # IP addresses
            r"([a-f\d]{1,4}:){3}[a-f\d]{1,4}::[a-f\d]{1,4}",
            r"100%  ?", # Sometimes an extra space appears after 100% for some reason.
        ]
        self.dir_redactors = [
            r"/tmp/tmp[A-Za-z0-9_]+", # Root dir
        ]
        os.chdir(self.dir)

    def tearDown(self):
        os.chdir(self.prior_dir)
        shutil.rmtree(self.dir)

    def test_protocol_https(self):
        finish(oracle.check_process(
            self,
            f"{binary} --no-config https://{HOST}/robots.txt",
            redactors=self.redactors
        ))
        oracle.check_directory(self, ".", redactors=self.dir_redactors)

    def test_protocol_http(self):
        finish(oracle.check_process(
            self,
            f"{binary} http://{HOST}/key/value",
            redactors=self.redactors
        ))
        oracle.check_directory(self, ".", redactors=self.dir_redactors)

    def test_protocol_ip(self):
        finish(oracle.check_process(
            self,
            f"{binary} --no-config --header 'Host: {HOST}' http://http://10.200.224.241/key/value",
            redactors=self.redactors
        ))
        oracle.check_directory(self, ".", redactors=self.dir_redactors)

    def test_opts_output(self):
        finish(oracle.check_process(
            self,
            f"{binary} --no-config -O data.json http://{HOST}/key/value/key2/value2",
            redactors=self.redactors
        ))
        oracle.check_directory(self, ".", redactors=self.dir_redactors)

    def test_opts_timeout_expired(self):
        finish(oracle.check_process(
            self,
            f"{binary} --no-config -T 2 http://echoss.{HOST}/",
            redactors=self.redactors
        ))
        oracle.check_directory(self, ".", redactors=self.dir_redactors)

    def test_get_param(self):
        finish(oracle.check_process(
            self,
            f"{binary} -O data.json http://md5.{HOST}/?text=hello_world",
            redactors=self.redactors
        ))
        oracle.check_directory(self, ".", redactors=self.dir_redactors)

    def test_no_args(self):
        finish(oracle.check_process(
            self,
            f"{binary}"
        ))
        oracle.check_directory(self, ".", redactors=self.dir_redactors)

    def test_help(self):
        finish(oracle.check_process(
            self,
            f"{binary} --help"
        ))
        oracle.check_directory(self, ".", redactors=self.dir_redactors)
