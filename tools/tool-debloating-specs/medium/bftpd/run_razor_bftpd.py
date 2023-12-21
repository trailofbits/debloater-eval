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

razor_helpers.binary = "bftpd"
execute = razor_helpers.execute
train_run = razor_helpers.train_run

@contextmanager
def bftpd(args):
    p = train_run(args, wait=False)
    try:
        yield p
    finally:
        p.terminate()

def lftp(*cmds):
    cmds = "\n".join(cmds + ("exit",))
    p = subprocess.Popen(
        shlex.split("lftp --rc lftp.rc"),
        stdin=subprocess.PIPE
    )

    p.communicate(input=cmds)
    return p

def put_file(name, contents):
    with open(name, 'w') as handle:
        handle.write(contents)


def transform_file(src, dest, replacements=dict()):
    with open(src, 'r') as input:
        with open(dest, 'w') as output:
            data = input.read()
            for to_replace, replacement in replacements.items():
                data = data.replace(to_replace, replacement)
            output.write(data)

def mkdirp(path):
    if os.path.exists(path):
        return True
    else:
        return os.mkdir(path)            

class Test_bftpd(unittest.TestCase):
    def setUp(self):
        replacements = {
            "{{trace.cwd}}": os.getcwd()
        }
        transform_file(
            "/input_files/bftpd-default-anon.conf",
            "default-anon.conf",
            replacements
        )
        transform_file(
            "/input_files/bftpd-disabled-cmds-anon.conf",
            "disabled-cmds-anon.conf",
            replacements
        )
        
        shutil.copytree("/input_files/bftpd-serve", "serve")
        shutil.copy("/input_files/lftp.rc", "lftp.rc")

    def tearDown(self):
        shutil.rmtree("serve")
        pass

    def test_get_file(self):
        with bftpd("-D -c default-anon.conf"):
            lftp("get file.txt")
        os.remove("file.txt")

    def test_navigate(self):
        with bftpd("-D -c default-anon.conf"):
            lftp(
                "ls",
                "cd child",
                "ls",
                "cd ..",
                "ls",
            )

    def test_chmod(self):
        with bftpd("-D -c default-anon.conf"):
            lftp(
                "chmod 440 file.txt"
            )

    def test_put(self):
        put_file("file", "hello world")
        with bftpd("-D -c default-anon.conf"):
            lftp(
                "put file"
            )
        os.remove("file")

    def test_mkdir(self):
        with bftpd("-D -c default-anon.conf"):
            lftp(
                "mkdir second"
            )

    def test_mv(self):
        with bftpd("-D -c default-anon.conf"):
            lftp(
                "mv file.txt file2.txt"
            )

    def test_pwd(self):
        with bftpd("-D -c default-anon.conf"):
            lftp(
                "cd ..",
                "cd ..",
                "pwd"
            )

    def test_rm(self):
        with bftpd("-D -c default-anon.conf"):
            lftp(
                "rm file.txt"
            )

    def test_pwd(self):
        mkdirp("serve/delete_me")
        with bftpd("-D -c default-anon.conf"):
            lftp(
                "rmdir delete_me",
            )

    # Disabled commands
    def test_rm_disabled(self):
        with bftpd("-D -c disabled-cmds-anon.conf"):
            lftp(
                "rm file.txt"
            )

    def test_rmdir_disabled(self):
        mkdirp("serve/delete_me")
        with bftpd("-D -c disabled-cmds-anon.conf"):
            lftp(
                "rmdir delete_me",
            )

    def test_chmod_disabled(self):
        with bftpd("-D -c disabled-cmds-anon.conf"):
            lftp(
                "chmod 440 file.txt"
            )

    def test_put_disabled(self):
        put_file("file", "hello world")
        with bftpd("-D -c disabled-cmds-anon.conf"):
            lftp(
                "put file"
            )

    def test_no_args(self):
        train_run("")

    def test_help(self):
        train_run("--help")

def train():
    suite = unittest.TestLoader().loadTestsFromTestCase(Test_bftpd)
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
