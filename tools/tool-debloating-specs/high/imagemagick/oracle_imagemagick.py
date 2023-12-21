from chisel_oracle import OracleHelper, finish
import tempfile
import os
import shutil
import unittest
from datetime import datetime, timedelta


binary = "[no binary specified]"
oracle = OracleHelper(__name__.replace("oracle_", ""))


def train_run(testcase, cmd):
    finish(oracle.check_process(testcase, str(binary) + " " + cmd))
    oracle.check_directory(testcase, ".")


class Oracle(unittest.TestCase):
    def setUp(self):
        self.maxDiff = None
        self.prior_dir = os.getcwd()
        self.dir = tempfile.mkdtemp()
        os.chdir(self.dir)
        for pic in ["eggs.bmp", "eggs.gif", "eggs.jpg", "eggs.png"]:
            shutil.copy("/input_files/{}".format(pic), self.dir)

    def tearDown(self):
        os.chdir(self.prior_dir)
        shutil.rmtree(self.dir)

    def test_convert_format(self):
        formats = ["jpg", "png", "bmp", "gif"]
        for frum in formats:
            for to in formats:
                train_run(self, "eggs.{} eggs2.{}".format(frum, to))

    def test_resized(self):
        for scale in ["50%"]: #, "150%"]:
            train_run(self, "eggs.jpg -resize {} eggs-resized.jpg")

    def test_flip(self):
        train_run(self, "eggs.jpg -flip eggs-flipped.jpg")

    def test_flop(self):
        train_run(self, "eggs.jpg -flop eggs-flopped.jpg")

    def test_negate(self):
        for flag in ["-negate", "+negate"]:
            train_run(self, "eggs.jpg {} eggs-negate.jpg".format(flag))

    def test_scale(self):
        for scale in ["50%"]: #, "150%"]:
            train_run(self, "eggs.jpg -scale {} eggs-scale.jpg")

    def test_roll(self):
        for x in ["+0", "-270"]: #, "+270"]:
            for y in ["+0", "-270"]: #, "+270"]:
                train_run(self, "eggs.jpg -roll {}{} eggs-rolled.jpg".format(x, y))

    def test_transverse(self):
        train_run(self, "eggs.jpeg -transverse eggs-transverse.jpg")

    def test_transpose(self):
        train_run(self, "eggs.jpg -transpose eggs-transposed.jpg")

    def test_rotate(self):
        for degrees in ["0", "-270", "-90", "90", "270", "360"]:
            train_run(self, "eggs.jpg -rotate {} eggs-transverse.jpg")

    def test_crop(self):
        for w in range(6, 399, 150):
            for h in range(6, 399, 150):
                for x in ["+0", "+90"]:
                    for y in ["+0", "+90"]:
                        train_run(self, "eggs.jpg -crop {}x{}{}{} eggs-cropped.jpg".format(w,h,x,y))
