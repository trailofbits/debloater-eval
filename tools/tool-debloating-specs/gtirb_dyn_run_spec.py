import unittest
import subprocess
import shlex
import os
import sys
import imp

binary = "[binary not specified]"

def execute(cmd, stdin_file=None, wait=True):
    cmd = shlex.split(cmd)
    print("running: ")
    print(cmd)
    if stdin_file:
        with open(stdin_file, 'rb') as stdin:
            p = subprocess.Popen(cmd, stdin=stdin)
            if wait:
                p.wait()
    else:
        p = subprocess.Popen(cmd)
        if wait:
            p.wait()
    return p


def train_run_cmd(args):
    if args:
        return " ".join([binary, args])
    else:
        return binary

def train_run(cmd, stdin_file=None, wait=True):
    cmd = train_run_cmd(cmd)
    return execute(cmd, stdin_file, wait)


def run(test_class):
    suite = unittest.TestLoader().loadTestsFromTestCase(test_class)
    unittest.TextTestRunner(verbosity=2).run(suite)


if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Usage: python3 %s [path to benchmark e.g. low/chown] [instrument binary]" % __file__)
        exit(1)
    path = sys.argv[1]
    benchmark = os.path.basename(path)
    binary = sys.argv[2]
    module_name = "%s.%s.run_razor_%s" % (
        path.split("/")[0],
        benchmark,
        benchmark
    )
    module_path = "/host/tool-debloating-specs/%s/run_razor_%s.py" % (
        path,
        benchmark
    )
    module = imp.load_source(module_name, module_path)
    setattr(module, "train_run_cmd", train_run_cmd)
    setattr(module, "train_run", train_run)
    setattr(module, "execute", execute)
    run(getattr(module, "Test_%s" % benchmark))
