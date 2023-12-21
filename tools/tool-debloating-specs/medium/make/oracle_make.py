from chisel_oracle import OracleHelper, finish
import tempfile
import os
import shutil
import unittest
from datetime import datetime, timedelta


binary = "[no binary specified]"
oracle = OracleHelper(__name__.replace("oracle_", ""))


def append(path, content):
    with open(path, 'a') as handle:
        handle.write(content)


class Oracle(unittest.TestCase):
    def setUp(self):
        self.prior_dir = os.getcwd()
        self.dir = tempfile.mkdtemp()
        self.maxDiff = None
        self.redactions = [
            # Temporary directories
            r"\/tmp\/[A-Za-z0-9_]+",
            # The name of the original binary binary during reduction
            r"make.orig",
            r"make",
        ]
        os.chdir(self.dir)
        shutil.copy("/input_files/low-custom_default_target.mak", self.dir)
        shutil.copy("/input_files/low-deps.mak", self.dir)
        shutil.copy("/input_files/low-multi_targets.mak", self.dir)
        shutil.copy("/input_files/low-single_target.mak", self.dir)
        shutil.copy("/input_files/med-phony.mak", self.dir)
        shutil.copy("/input_files/high-includes.mak", self.dir)
        shutil.copy("/input_files/high-vars.mak", self.dir)

    def use(self, name):
        shutil.copy(name + ".mak", "Makefile")

    def tearDown(self):
        os.chdir(self.prior_dir)
        shutil.rmtree(self.dir)

    def test_low_single_target(self):
        self.use("low-single_target")
        finish(oracle.check_process(
            self,
            "{} file1".format(binary)
        ))
        oracle.check_directory(self, ".")

    def test_low_multiple_targets(self):
        self.use("low-multi_targets")
        finish(oracle.check_process(
            self,
            "{} file1 file2".format(binary)
        ))
        oracle.check_directory(self, ".")

    def test_low_deps(self):
        self.use("low-deps")
        finish(oracle.check_process(
            self,
            "{} file3".format(binary)
        ))
        oracle.check_directory(self, ".")

    def test_low_deps_update(self):
        self.use("low-deps")
        # Goal: rebuild file3 but do not rebuild deps
        finish(oracle.check_process(
            self,
            "{} file3".format(binary)
        ))
        shutil.copy("file3", "file3-original")
        append("file3-original", "more")
        append("deps", "more")
        shutil.copy("deps", "deps-original")
        append("file3", "asdf")
        mod_time = datetime.now() - timedelta(days=3)
        mod_time = mod_time - datetime(1970,1,1)
        os.utime("file3", (mod_time.total_seconds(), mod_time.total_seconds()))
        finish(oracle.check_process(
            self,
            "{} file3".format(binary)
        ))
        oracle.check_directory(self, ".")

    def test_low_deps_up_to_date(self):
        self.use("low-deps")
        finish(oracle.check_process(
            self,
            "{} file3".format(binary)
        ))
        oracle.check_directory(self, ".")
        finish(oracle.check_process(
            self,
            "{} file3".format(binary)
        ))
        oracle.check_directory(self, ".")

    def test_low_default_target(self):
        self.use("low-single_target")
        finish(oracle.check_process(
            self,
            "{} ".format(binary)
        ))
        oracle.check_directory(self, ".")

    def test_low_custom_default_target(self):
        self.use("low-custom_default_target")
        finish(oracle.check_process(
            self,
            "{} ".format(binary)
        ))
        oracle.check_directory(self, ".")

    def test_low_args_file_stdin(self):
        with open("low-single_target.mak", "r") as makefile:
            finish(oracle.check_process(
                self,
                "{} -f - file1".format(binary),
                stdin=makefile.read(),
                redactors=self.redactions
            ))
        oracle.check_directory(self, ".")

    def test_low_args_file(self):
        finish(oracle.check_process(
            self,
            "{} -f low-single_target.mak file1".format(binary),
            redactors=self.redactions
        ))
        oracle.check_directory(self, ".")

    def test_med_phony(self):
        self.use("med-phony")
        finish(oracle.check_process(
            self,
            "{} all".format(binary)
        ))
        oracle.check_directory(self, ".")

    def test_high_includes(self):
        self.use("high-includes")
        finish(oracle.check_process(
            self,
            "{} file4".format(binary)
        ))
        oracle.check_directory(self, ".")

    def test_high_vars(self):
        self.use("high-vars")
        finish(oracle.check_process(
            self,
            "{} install".format(binary),
            redactors=self.redactions
        ))
        oracle.check_directory(self, ".")

    def test_no_args(self):
        finish(oracle.check_process(
            self,
            "{}".format(binary)
        ))

    def test_no_args(self):
        finish(oracle.check_process(
            self,
            "{} -help".format(binary)
        ))
