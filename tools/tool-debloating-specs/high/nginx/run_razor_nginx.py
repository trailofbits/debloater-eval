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


razor_helpers.binary = "nginx"
execute = razor_helpers.execute
train_run = razor_helpers.train_run

def mkdirp(path):
    if os.path.exists(path):
        return path
    else:
        return os.mkdir(path)

def wget(args):
    assert type(args) == str
    subprocess.call(shlex.split("wget " + args))

class Test_nginx(unittest.TestCase):
    def setUp(self):
        os.chmod(os.getcwd(), 0o777)
        mkdirp("logs")
        for root, dirs, files in os.walk(os.getcwd()):
            for dir in dirs:
                os.chmod(os.path.join(root, dir), 0o0777)
            for file in files:
                os.chmod(os.path.join(root, file), 0o0777)
        shutil.copytree("/input_files/nginx-serve-ip", "serve-ip")
        shutil.copy("/input_files/nginx-file_server.conf", "file_server.conf")
        self.proc = train_run("-p {} -c file_server.conf".format(os.getcwd()), wait=False)
        time.sleep(1.0)

    def tearDown(self):
        self.proc.terminate()
        time.sleep(1.0)
        shutil.rmtree("serve-ip")

    def test_file_server_download(self):
        wget("http://127.0.0.1:8080/dir1/file1.html")
        wget("http://127.0.0.1:8080/dir1/./../about.html")
        wget("-O index.html http://127.0.0.1:8080")

    def test_file_server_download_404(self):
        wget("http://127.0.0.1:8080/dir2/about.html")

def train():
    suite = unittest.TestLoader().loadTestsFromTestCase(Test_nginx)
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
