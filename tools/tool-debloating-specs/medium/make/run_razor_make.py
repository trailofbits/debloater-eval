#!/usr/bin/python

# Originally copied from the core-utilities/grep-2.19 benchmark 

from __future__ import print_function
import os, subprocess, sys
import tempfile
import unittest
import shutil
import shlex
import time
from datetime import datetime, timedelta

import razor_helpers


razor_helpers.binary = "make"
execute = razor_helpers.execute
train_run = razor_helpers.train_run


def append(path, content):
    with open(path, 'a') as handle:
        handle.write(content)

class Test_make(unittest.TestCase):
    def setUp(self):
        shutil.copy("/input_files/low-custom_default_target.mak", "./")
        shutil.copy("/input_files/low-deps.mak", "./")
        shutil.copy("/input_files/low-multi_targets.mak", "./")
        shutil.copy("/input_files/low-single_target.mak", "./")
        shutil.copy("/input_files/med-phony.mak", "./")
        shutil.copy("/input_files/high-includes.mak", "./")
        shutil.copy("/input_files/high-vars.mak", "./")

    def tearDown(self):
        files = [
            "file1",
            "file2",
            "file3",
            "file4",
            "deps"
        ]
        for f in files:
            subprocess.check_call(shlex.split("rm -f %s" % f))
        pass

    def use(self, name):
        shutil.copy(name + ".mak", "Makefile")

    def test_low_single_target(self):
        self.use("low-single_target")
        train_run("file1")

    def test_low_multiple_targets(self):
        self.use("low-multi_targets")
        train_run("file1 file2")

    def test_low_deps(self):
        self.use("low-deps")
        train_run("file3")

    def test_low_deps_update(self):
        self.use("low-deps")
        # Goal: rebuild file3 but do not rebuild deps
        train_run("file3")
        shutil.copy("file3", "file3-original")
        append("file3-original", "more")
        append("deps", "more")
        shutil.copy("deps", "deps-original")
        append("file3", "asdf")
        mod_time = datetime.now() - timedelta(days=3)
        mod_time = mod_time - datetime(1970,1,1)
        os.utime("file3", (mod_time.total_seconds(), mod_time.total_seconds()))
        train_run("file3")
        os.remove("file3-original")
        os.remove("deps-original")

    def test_low_deps_up_to_date(self):
        self.use("low-deps")
        train_run("file3")
        train_run("file3")

    def test_low_default_target(self):
        self.use("low-single_target")
        train_run("")

    def test_low_custom_default_target(self):
        self.use("low-custom_default_target")
        train_run("")

    def test_low_args_file_stdin(self):
        train_run("-f - file1", stdin_file="low-single_target.mak")

    def test_low_args_file(self):
        train_run("-f low-single_target.mak file1")

    def test_med_phony(self):
        self.use("med-phony")
        train_run("all")

    def test_high_includes(self):
        self.use("high-includes")
        train_run("file4")

    def test_high_vars(self):
        self.use("high-vars")
        train_run("install")
        shutil.rmtree("build")

    def test_no_args(self):
        train_run("")

    def test_help(self):
        train_run("--help")

def train():
    suite = unittest.TestLoader().loadTestsFromTestCase(Test_make)
    unittest.TextTestRunner(verbosity=2).run(suite)
    return

def debloat(logs_dir, prog_name):
    razor_helpers.razor_execute("""python ../../../stitcher/src/merge_log.py %s %s""" % (logs_dir, prog_name))
    razor_helpers.razor_execute("""mv %s/%s-trace.log ./""" % (logs_dir, prog_name))
    razor_helpers.razor_execute("""python ../../../stitcher/src/instr_dumper.py ./%s-trace.log ./%s.orig ./instr.s""" % (prog_name, prog_name))
    razor_helpers.razor_execute("""python ../../../stitcher/src/find_symbols.py ./%s.orig ./instr.s > ./callbacks.txt""" % (prog_name))
    razor_helpers.razor_execute("""python ../../../stitcher/src/stitcher.py ./%s-trace.log ./%s.orig ./%s.s ./callbacks.txt""" % (prog_name, prog_name, prog_name))
    razor_helpers.razor_execute("""python ../../../stitcher/src/merge_bin.py %s.orig %s.s""" % (prog_name, prog_name))

def usage():
    print('python run_razor.py train|debloat\n')
    sys.exit(1)

def main():
    if len(sys.argv) != 2 and len(sys.argv) != 3:
        usage()

    if not os.path.exists("./logs"):
        cmd = "mkdir -p ./logs"
        execute(cmd)

        cmd = "cp ../../../tracers/bin/libcbr_indcall.so ./logs/"
        execute(cmd)
    
    if sys.argv[1] == 'train':
        train()

    elif sys.argv[1] == 'debloat':
        debloat('logs', razor_helpers.binary)

    else:
        usage()

if __name__ == '__main__':
    main()
