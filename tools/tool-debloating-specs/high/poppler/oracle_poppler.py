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
    finish(oracle.check_process(testcase, str(binary) + " " + cmd))
    oracle.check_directory(testcase, ".")


class Oracle(unittest.TestCase):
    def setUp(self):
        self.maxDiff = None
        self.dir = tempfile.mkdtemp()
        self.prior_dir = os.getcwd()
        os.chdir(self.dir)
        shutil.copy("/input_files/BinRec.pdf", "BinRec.pdf")
        shutil.copy("/input_files/markdown.pdf", "markdown.pdf")
        shutil.copy("/input_files/openpdf.zip", "openpdf.zip")
        subprocess.check_call(shlex.split("unzip openpdf.zip"))

    def tearDown(self):
        os.chdir(self.prior_dir)
        shutil.rmtree(self.dir)

    def test_markdown(self):
        train_run(self, "markdown.pdf")

    def test_opts_range(self):
        train_run(self, "-f 1 -l 1 markdown.pdf")

    def test_opts_single_doc(self):
        train_run(self, "-s markdown.pdf")

    def test_opts_stdout(self):
        train_run(self, "-stdout markdown.pdf")

    def test_images(self):
        train_run(self, "BinRec.pdf")

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
            train_run(self, "{} output.html".format(f))
