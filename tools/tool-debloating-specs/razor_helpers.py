import subprocess
import shlex

def razor_execute(cmd):
    print('running ', cmd)
    p = subprocess.Popen(cmd, shell=True)
    p.communicate()


def execute(cmd, stdin_file=None, wait=True):
    cmd = shlex.split(cmd)
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


DRRUN = '../../../tracers/dynamorio/bin64/drrun'
CLIENT = './logs/libcbr_indcall.so'

binary = "[binary not specified]"

def train_run_cmd(arg):
    BIN = './{}.orig'.format(binary)
    if arg:
        cmd = " ".join([BIN, arg])
    else:
        cmd = BIN
    return DRRUN + ' -c ' + CLIENT + ' -- ' + cmd

def train_run(arg, stdin_file=None, wait=True):
    cmd = train_run_cmd(arg)
    return execute(cmd, stdin_file, wait=wait)

