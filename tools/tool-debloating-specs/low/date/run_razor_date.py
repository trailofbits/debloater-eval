#!/usr/bin/python

# Originally copied from the core-utilities/grep-2.19 benchmark 

from __future__ import print_function
import os, subprocess, sys
import tempfile
import unittest
import shutil
import shlex
from itertools import chain, combinations 

import razor_helpers


razor_helpers.binary = "date"
execute = razor_helpers.execute
train_run = razor_helpers.train_run
train_run_cmd = razor_helpers.train_run_cmd


def powerset(iterable):
    s = list(iterable)
    return chain.from_iterable(combinations(s, r) for r in range(len(s)+1))


class Test_date(unittest.TestCase):
    def setUp(self):
        shutil.copy("/input_files/date/datefile", "datefile")

    def tearDown(self):
        os.remove("datefile")

    def test_script(self):
        shutil.copy("/host/tool-debloating-specs/low/date/oracle.sh", "./")
        cmd = train_run_cmd("")
        subprocess.check_call(
            "sed -i 's#REDUCED_BIN=./src/date#REDUCED_BIN=\"%s\"#' oracle.sh" % cmd,
            shell=True
        )
        subprocess.check_call(
            "sed -i 's#ORIGIN_BIN=./date.origin#ORIGIN_BIN=./date.orig#' oracle.sh",
            shell=True
        )
        subprocess.check_call("./oracle.sh")
        os.remove("./oracle.sh")

def train():
    suite = unittest.TestLoader().loadTestsFromTestCase(Test_date)
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
