#!/usr/bin/python

# Originally copied from the core-utilities/grep-2.19 benchmark 

from __future__ import print_function
import os, subprocess, sys
import tempfile
import unittest
import shutil
import shlex
import time
from pymemcache.client import base
from contextlib import contextmanager
import time

import razor_helpers


razor_helpers.binary = "memcached"
execute = razor_helpers.execute
train_run = razor_helpers.train_run

@contextmanager
def memcached():
    p = train_run("", wait=False)
    try:
        time.sleep(1.0)
        yield p
    finally:
        p.terminate()
        time.sleep(1.0)

class Test_memcached(unittest.TestCase):
    def setUp(self):
        pass

    def tearDown(self):
        pass

    def test_set_get(self):
        with memcached():
            client = base.Client('127.0.0.1')
            client.set('x', '10')
            client.get('x')

    def test_set_expiration_get_expired(self):
        with memcached():
            client = base.Client('127.0.0.1')
            client.set('x', '10', expire=2)
            client.get('x')
            time.sleep(3.0)
            client.get('x')

    def test_add(self):
        with memcached():
            client = base.Client('127.0.0.1')
            client.add('x', '10')
            client.get('x')

    def test_add_exists(self):
        with memcached():
            client = base.Client('127.0.0.1')
            client.set('x', '10')
            client.add('x', '20')
            client.get('x')

    def test_replace(self):
        with memcached():
            client = base.Client('127.0.0.1')            
            client.add('x', '10')
            client.replace('x', '20')

    def test_replace_nonexistent(self):
        with memcached():
            client = base.Client('127.0.0.1')            
            client.replace('x', '10')

    def test_append(self):
        with memcached():
            client = base.Client('127.0.0.1')            
            client.add('x', '10')
            client.append('x', '10')

    def test_append_nonexistent(self):
        with memcached():
            client = base.Client('127.0.0.1')            
            client.append('x', '10')

    def test_prepend(self):
        with memcached():
            client = base.Client('127.0.0.1')            
            client.add('x', '10')
            client.prepend('x', '00')

    def test_prepend_nonexistent(self):
        with memcached():
            client = base.Client('127.0.0.1')            
            client.prepend('x', '00')

    def test_delete(self):
        with memcached():
            client = base.Client('127.0.0.1')            
            client.add('x', '10')
            client.delete('x')

    def test_delete_nonexistent(self):
        with memcached():
            client = base.Client('127.0.0.1')            
            client.delete('x')

    def test_incr(self):
        with memcached():
            client = base.Client('127.0.0.1')            
            client.set('x', '10')
            client.incr('x', 1)

    def test_incr_nonexistent(self):
        with memcached():
            client = base.Client('127.0.0.1')            
            client.incr('x', 1)

    def test_decr(self):
        with memcached():
            client = base.Client('127.0.0.1')            
            client.set('x', '10')
            client.decr('x', 1)

    def test_decr_nonexistent(self):
        with memcached():
            client = base.Client('127.0.0.1')            
            client.decr('x', 1)

    def test_no_args(self):
        with memcached():
            pass

    def test_help(self):
        train_run("--help")


def train():
    suite = unittest.TestLoader().loadTestsFromTestCase(Test_memcached)
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
