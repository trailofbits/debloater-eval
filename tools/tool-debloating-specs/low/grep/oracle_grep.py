#!/usr/bin/python

# Originally copied from the core-utilities/grep-2.19 benchmark 

from chisel_oracle import OracleHelper, finish, terminate
import tempfile
import os
import shutil
import unittest
import socket
from contextlib import contextmanager


binary = "[no binary specified]"
oracle = OracleHelper(__name__.replace("oracle_", ""))


def train_run(testcase, cmd):
    finish(oracle.check_process(testcase, binary + " " + cmd))
    oracle.check_directory(testcase, ".")


def touch(path):
    handle = open(path, 'w')
    handle.close()
    return path


class Oracle(unittest.TestCase):
    def setUp(self):
        self.dir = tempfile.mkdtemp()
        self.prior_dir = os.getcwd()
        os.chdir(self.dir)
        os.mkdir("input_dir")
        shutil.copy("/input_files/grep-data", "foo")
        shutil.copy("/input_files/grep-data", "input_dir/foo")
        shutil.copy("/input_files/grep-data", "input_dir/input2")

    def tearDown(self):
        os.chdir(self.prior_dir)
        shutil.rmtree(self.dir)

    def test_all(self):
        train_run(self, "a dir/foo")
        train_run(self, "a -v -H -r input_dir")
        train_run(self, "1 -h -r input_dir")
        train_run(self, "-n si input_dir/input2")
        train_run(self, "1 -r input_dir -l")
        train_run(self, "1 -r input_dir -L")
        train_run(self, "randomtext -r input_dir -c")
        train_run(self, "-o [r][a][n][d]* input_dir/input2")
        train_run(self, "1 -r input_dir -q")
        train_run(self, "1 -r input_dir -s")
        train_run(self, "-v a input_dir/input2")
        train_run(self, "-i Si input_dir/input2")
        train_run(self, "-w Si input_dir/input2")
        train_run(self, "-x Don\\'t input_dir/input2")
        train_run(self, "-E randomtext* input_dir/input2")
        train_run(self, "ye input_dir/input")
        train_run(self, "cold input_dir/input")
        train_run(self, "^D input_dir/input2")
        train_run(self, ".$ input_dir/input2")
        train_run(self, "\^ input_dir/input2")
        train_run(self, "\^$ input_dir/input2")
        train_run(self, "^[AEIOU] input_dir/input2")
        train_run(self, "^[^AEIOU] input_dir/input2")
        train_run(self, "-F randomtext* input_dir/input2")
        train_run(self, "not_exist input_dir/input")
        train_run(self, "-E free[^[:space:]]+ input_dir/input2")
        train_run(self, "-E \b(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?) input_dir/input")

