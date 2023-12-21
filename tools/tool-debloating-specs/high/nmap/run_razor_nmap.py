#!/usr/bin/python

# Originally copied from the core-utilities/grep-2.19 benchmark 

from __future__ import print_function
import os, subprocess, sys
import tempfile
import unittest
import shutil
import shlex
from contextlib import contextmanager

import razor_helpers


razor_helpers.binary = "nmap"
execute = razor_helpers.execute
train_run = razor_helpers.train_run


@contextmanager
def tcp(port, content):
    p = subprocess.Popen(
        shlex.split("nc -l {}".format(port)),
        stdin=subprocess.PIPE
    )
    p.stdin.write(content)
    try:
        yield p
    finally:
        p.terminate()

@contextmanager
def http(port, directory):
    p = subprocess.Popen(
        shlex.split("python -m SimpleHTTPServer {}".format(port)),
        cwd=directory
    )
    try:
        yield p
    finally:
        p.terminate()

class Test_nmap(unittest.TestCase):
    def setUp(self):
        shutil.copytree("/input_files/nmap-serve", "serve")

    def tearDown(self):
        shutil.rmtree("serve")
        pass

    def test_tcp_port_scan(self):
        with tcp(8080, "hello world\n"):
            train_run("-sT 127.0.0.1")

    def test_tcp_port_scan_range(self):
        with tcp(8080, "hello world\n"):
            with tcp(8081, "you should not see this\n"):
                with tcp(7080, "you should see this\n"):
                    train_run("-sT -p1-7080,8080 127.0.0.1")

    def test_service_scan(self):
        with http(8080, "serve"):
            train_run("-sT -sV 127.0.0.1")

    def test_service_scan_output(self):
        with http(8080, "serve"):
            for output_flag in ["-oG", "-oN", "-oX"]:
                train_run("-sT -sV {} report 127.0.0.1".format(output_flag))

def train():
    suite = unittest.TestLoader().loadTestsFromTestCase(Test_nmap)
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
