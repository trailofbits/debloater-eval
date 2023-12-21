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


razor_helpers.binary = "magick"
execute = razor_helpers.execute
train_run = razor_helpers.train_run


class Test_imagemagick(unittest.TestCase):
    def setUp(self):
        for pic in ["eggs.bmp", "eggs.gif", "eggs.jpg", "eggs.png"]:
            shutil.copy("/input_files/{}".format(pic), os.getcwd())

    def tearDown(self):
        pass

    def test_convert_format(self):
        formats = ["jpg", "png", "bmp", "gif"]
        for frum in formats:
            for to in formats:
                train_run("eggs.{} eggs2.{}".format(frum, to))

    def test_resized(self):
        for scale in ["50%", "150%"]:
            train_run("eggs.jpg -resize {} eggs-resized.jpg".format(scale))

    def test_flip(self):
        train_run("eggs.jpg -flip eggs-flipped.jpg")

    def test_flop(self):
        train_run("eggs.jpg -flop eggs-flopped.jpg")

    def test_negate(self):
        for flag in ["-negate", "+negate"]:
            train_run("eggs.jpg {} eggs-negate.jpg".format(flag))

    def test_scale(self):
        for scale in ["50%", "150%"]:
            train_run("eggs.jpg -scale {} eggs-scale.jpg".format(scale))

    def test_roll(self):
        for x in ["+0", "-270", "+270"]:
            for y in ["+0", "-270", "+270"]:
                train_run("eggs.jpg -roll {}{} eggs-rolled.jpg".format(x, y))

    def test_transverse(self):
        train_run("eggs.jpg -transverse eggs-transverse.jpg")

    def test_transpose(self):
        train_run("eggs.jpg -transpose eggs-transposed.jpg")

    def test_rotate(self):
        for degrees in ["0", "-270", "-90", "90", "270", "360"]:
            train_run("eggs.jpg -rotate {} eggs-transverse.jpg".format(degrees))

    def test_crop(self):
        for w in range(6, 399, 150):
            for h in range(6, 399, 150):
                for x in ["+0", "+90"]:
                    for y in ["+0", "+90"]:
                        train_run("eggs.jpg -crop {}X{}{}{} eggs-cropped.jpg".format(w,h,x,y))

def train():
    suite = unittest.TestLoader().loadTestsFromTestCase(Test_imagemagick)
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

# LD_LIBRARY_PATH=MagickCore/.libs/:MagickWand/.libs/:$LD_LIBRARY_PATH
# MAGICK_CONFIGURE_PATH=$(pwd)/config LD_LIBRARY_PATH=MagickCore/.libs/:MagickWand/.libs/:$LD_LIBRARY_PATH
# PYTHONPATH="/host/tool-debloating-specs:$PYTHONPATH"
