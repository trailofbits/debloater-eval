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
import time

import razor_helpers


razor_helpers.binary = "lighttpd"
execute = razor_helpers.execute
train_run = razor_helpers.train_run


@contextmanager
def lighttpd(args):
    p = train_run(args, wait=False)
    try:
        time.sleep(1.0)
        yield p
    finally:
        p.terminate()

def wget(args):
    assert type(args) == str
    subprocess.call(shlex.split("wget " + args))

def mkdirp(path):
    if os.path.exists(path):
        return True
    else:
        return os.mkdir(path)

def put_file(filename, content):
    dir = os.path.dirname(filename)
    subprocess.check_call(shlex.split("mkdir -p %s" % dir))
    with open(filename, 'w') as f:
        f.write(content)


def transform_file(src, dest, replacements=dict()):
    with open(src, 'r') as input:
        with open(dest, 'w') as output:
            data = input.read()
            for to_replace, replacement in replacements.items():
                data = data.replace(to_replace, replacement)
            output.write(data)


class Test_lighttpd(unittest.TestCase):
    def setUp(self):
        put_file("serve-vhost/hello.text", "hello world")
        shutil.copytree("/input_files/lighttpd-serve", "serve")
        configs = {
            "/input_files/lighttpd-static-all.conf": "static-all.conf",
            "/input_files/lighttpd-static-exclude-php.conf": "static-exclude-php.conf",
            "/input_files/lighttpd-static-index.conf": "static-index.conf",
            "/input_files/lighttpd-static-vhost.conf": "static-vhost.conf",
        }
        for src, dest in configs.items():
            transform_file(src, dest, {"{{trace.cwd}}": os.getcwd()})

    def tearDown(self):
        shutil.rmtree("serve")
        pass

    def test_get_root_file(self):
        with lighttpd("-D -f static-all.conf"):
            wget("http://localhost:3000/index.html")

    def test_get_nested_file(self):
        with lighttpd("-D -f static-all.conf"):
            wget("http://localhost:3000/dir1/file1.html")

    def test_get_index(self):
        with lighttpd("-D -f static-index.conf"):
            wget("http://localhost:3000")

    def test_get_include_ext(self):
        with lighttpd("-D -f static-exclude-php.conf"):
            wget("http://localhost:3000/index.html")

    def test_get_exclude_ext(self):
        with lighttpd("-D -f static-exclude-php.conf"):
            wget("http://localhost:3000/run.php")

    def test_get_vhost_1(self):
        with lighttpd("-D -f static-vhost.conf"):
            wget("http://127.0.0.1:3000/index.html")

    def test_get_vhost_2(self):
        with lighttpd("-D -f static-vhost.conf"):
            wget("http://127.0.0.1:3000/hello.txt")

    def test_get_vhost_3(self):
        with lighttpd("-D -f static-vhost.conf"):
            wget("http://127.0.1.1:3000/hello.txt")

    def test_get_404(self):
        with lighttpd("-D -f static-all.conf"):
            wget("http://localhost:3000/foo.html")

    def test_no_args(self):
        train_run("")

    def test_help(self):
        train_run("-help")


def train():
    suite = unittest.TestLoader().loadTestsFromTestCase(Test_lighttpd)
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

