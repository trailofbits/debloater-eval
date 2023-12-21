#!/usr/bin/python

# Originally copied from the core-utilities/grep-2.19 benchmark 

from __future__ import print_function
import os, subprocess, sys
import tempfile
import unittest
import shutil
import shlex
import time
from contextlib import contextmanager

import razor_helpers


razor_helpers.binary = "pdftohtml"
execute = razor_helpers.execute
train_run = razor_helpers.train_run


class Test_poppler(unittest.TestCase):
    def setUp(self):
        shutil.copy("/input_files/BinRec.pdf", "BinRec.pdf")
        shutil.copy("/input_files/markdown.pdf", "markdown.pdf")
        shutil.copy("/input_files/openpdf.zip", "openpdf.zip")
        subprocess.check_call("unzip openpdf.zip".split())

    def tearDown(self):
        subprocess.check_call("rm *.pdf", shell=True)
        pass

    def test_markdown(self):
        train_run("markdown.pdf")

    def test_opts_range(self):
        train_run("-f 1 -l 1 markdown.pdf")

    def test_opts_single_doc(self):
        train_run("-s markdown.pdf")

    def test_opts_stdout(self):
        train_run("-stdout markdown.pdf")

    def test_images(self):
        train_run("BinRec.pdf")

    def test_openpdf_corpus(self):
        files = [
            "OPENPDF-129-0.pdf",
            "OPENPDF-129-1.pdf",
            "OPENPDF-129-2.pdf",
            "OPENPDF-129-3.pdf",
            "OPENPDF-129-4.pdf",
            "OPENPDF-156-0.pdf",
            "OPENPDF-156-1.pdf",
            "OPENPDF-179-0.pdf",
            "OPENPDF-179-1.pdf",
            "OPENPDF-179-2.pdf",
            "OPENPDF-216-0.pdf",
            "OPENPDF-216-1.pdf",
            "OPENPDF-216-2.pdf",
            "OPENPDF-254-0.zip-0.pdf",
            "OPENPDF-254-0.zip-2.pdf",
            "OPENPDF-296-0.pdf",
            "OPENPDF-296-1.pdf",
            "OPENPDF-296-2.pdf",
            "OPENPDF-296-3.pdf",
            "OPENPDF-296-4.pdf",
            "OPENPDF-296-5.pdf",
            "OPENPDF-330-0.pdf",
            "OPENPDF-65-0.pdf",
            "OPENPDF-73-0.pdf",
            "OPENPDF-86-0.pdf",
            "OPENPDF-86-1.pdf",
            "OPENPDF-9-0.pdf",
            "OPENPDF-LINK-158-0.pdf",
            "OPENPDF-LINK-320-0.pdf",
            "OPENPDF-LINK-320-1.pdf",
            "OPENPDF-LINK-86-0.pdf"
        ]
        for f in files:
            train_run("{} output.html".format(f))

def train():
    suite = unittest.TestLoader().loadTestsFromTestCase(Test_poppler)
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

#cmake -DCMAKE_BUILD_TYPE=release -DCMAKE_C_FLAGS="-O3" -DCMAKE_CXX_FLAGS="-O3  " -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang
