#!/usr/bin/python

# Originally copied from the core-utilities/grep-2.19 benchmark 

from __future__ import print_function
import os, subprocess, sys
import tempfile
import unittest
import shutil
import shlex

import socket

import razor_helpers


razor_helpers.binary = "/binaries/wget"
execute = razor_helpers.execute
train_run = razor_helpers.train_run


class Test_wget(unittest.TestCase):
    def setUp(self):
        pass

    def tearDown(self):
        pass

    def test_protocol_https(self):
        train_run("--no-config https://digg.com/robots.txt")
        os.remove("robots.txt")

    def test_protocol_http(self):
        train_run("http://echo.jsontest.com/key/value")
        os.remove("value")

    def test_protocol_ip(self):
        ip = socket.gethostbyname('echo.jsontest.com')
        train_run("--no-config --header 'Host: echo.jsontest.com' http://{}/key/value".format(ip))
        os.remove("value")

    def test_opts_output(self):
        train_run("--no-config -O data.json http://echo.jsontest.com/key/value/key2/value2")
        os.remove("data.json")

    def test_opts_timeout_expired(self):
        train_run("--no-config -T 2 http://echoss.jsontest.com/")

    def test_get_param(self):
        train_run("--no-config -O data.json http://md5.jsontest.com/?text=hello_world")

    def test_no_args(self):
        train_run("")

    def test_help(self):
        train_run("--help")

def train():
    suite = unittest.TestLoader().loadTestsFromTestCase(Test_wget)
    unittest.Test_wget(verbosity=2).run(suite)
    return

def debloat(logs_dir, prog_name):
    execute("""python ../../../stitcher/src/merge_log.py %s %s""" % (logs_dir, prog_name))
    execute("""mv %s/%s-trace.log ./""" % (logs_dir, prog_name))
    execute("""python ../../../stitcher/src/instr_dumper.py ./%s-trace.log ./%s.orig ./instr.s""" % (prog_name, prog_name))
    execute("""python ../../../stitcher/src/find_symbols.py ./%s.orig ./instr.s > ./callbacks.txt""" % (prog_name))
    execute("""python ../../../stitcher/src/stitcher.py ./%s-trace.log ./%s.orig ./%s.s ./callbacks.txt""" % (prog_name, prog_name, prog_name))
    execute("""python ../../../stitcher/src/merge_bin.py %s.orig %s.s""" % (prog_name, prog_name))

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
        debloat('logs', binary)

    else:
        usage()

if __name__ == '__main__':
    main()
