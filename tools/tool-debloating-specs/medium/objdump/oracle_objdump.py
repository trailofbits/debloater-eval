from chisel_oracle import OracleHelper, finish
import tempfile
import os
import shutil
import unittest

binary = "[no binary specified]"
oracle = OracleHelper(__name__.replace("oracle_", ""))

class Oracle(unittest.TestCase):
    def setUp(self):
        self.dir = tempfile.mkdtemp()
        self.prior_dir = os.getcwd()
        os.chdir(self.dir)

    def tearDown(self):
        os.chdir(self.prior_dir)
        shutil.rmtree(self.dir)

    def test_exec_dyn_static(self):
        flags = [
            "-a",
            "-f",
            "-p",
            "-h",
            "-x",
            "-d",
            "-D",
            "-S",
            "-s",
            "-g",
            "-e",
            "-G",
            "-t",
            "-r"
        ]
        # These binaries were copied from the razor image
        # 
        # real	1m12.654s
        # user	1m12.619s
        # sys	0m0.299s
        binaries = [
            "/input_files/libpthread.a",
            "/input_files/libc-2.28.so",
            "/input_files/x86_64-linux-gnu-gcc-8"
        ]
        # real	0m1.503s
        # user	0m1.490s
        # sys	0m0.029s
        binaries = [
            "/usr/lib/gcc/x86_64-linux-gnu/9/libssp_nonshared.a",
            "/usr/lib/x86_64-linux-gnu/libutil-2.31.so",
            "/usr/bin/x86_64-linux-gnu-strings",
        ]
        for flag in flags:
            for test_binary in binaries:
                finish(oracle.check_process(self, "{} {} {}".format(binary, flag, test_binary)))

    def test_dyn_tables(self):
        flags = ["-T", "-R"]
        # real	1m12.654s
        # user	1m12.619s
        # sys	0m0.299s
        binaries = [
            "/input_files/libc-2.28.so",
            "/input_files/x86_64-linux-gnu-gcc-8"
        ]
        # real	0m1.503s
        # user	0m1.490s
        # sys	0m0.029s
        binaries = [
            "/usr/lib/x86_64-linux-gnu/libutil-2.31.so",
            "/usr/bin/x86_64-linux-gnu-strings",
        ]
        for flag in flags:
            for test_binary in binaries:
                finish(oracle.check_process(self, "{} {} {}".format(binary, flag, test_binary)))

    def test_help(self):
        oracle.check_process(self, "{} --help".format(binary))

    def test_no_args(self):
        oracle.check_process(self, "{} ".format(binary))
