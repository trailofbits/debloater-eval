import subprocess
import shlex
from pathlib import Path
import argparse
import importlib
from contextlib import contextmanager
import unittest
import sys
import os
import yaml
import re


def terminate(p, stdin):
    """
    Describes how to finish a process with terminate(), to be used with
    check_process.  The value of stdin is not passed to the process.
    """
    if p.poll() is None:
        p.terminate()
        p.wait()
    return (p.stdout.read(), p.stderr.read())


def communicate(proc, stdin):
    """
    Describes how to finish a process with communicate(), to be used with
    check_process.
    """
    return proc.communicate(stdin)


def finish(proc):
    """
    Runs a process returned by check_process to completion.
    """
    proc.__enter__()
    proc.__exit__(None, None, None)


def is_text(filename):
    """
    True if filename contains ascii text according to the file utility.
    False otherwise.
    """
    p = subprocess.run(
        shlex.split(f"file {filename}"),
        stdout=subprocess.PIPE,
        check=True,
        encoding="utf-8"
    )
    return "text" in p.stdout


def dir_tree_to_dict(root, redactors=[]):
    """
    Captures the structure of -- and content of files in -- a directory tree
    into a dictionary, for serialization or comparison.  Also captures the
    permissions of the directories and files.

    root: The root of the directory tree.
    redactors: Redactors passed to the redact function, which will operate
               on file contents.
    returns: A dictionary representing the structure, contents, and
    permissions of the directory tree.
    """
    result = dict()
    for dirpath, dirs, files in os.walk(root):
        dirs = [os.path.join(dirpath, d) for d in dirs]
        files = [os.path.join(dirpath, f) for f in files]
        for d in dirs:
            result[d] = {
                "type": "directory",
                "perms": os.stat(d).st_mode
            }
        for f in files:
            if is_text(f):
                with open(f, 'r') as handle:
                    result[f] = {
                        "type": "file",
                        "content": redact(handle.read(), redactors),
                        "perms": os.stat(f).st_mode
                    }
            else:
                with open(f, 'rb') as handle:
                    result[f] = {
                        "type": "file",
                        "content": handle.read(),
                        "perms": os.stat(f).st_mode
                    }

    return result


def redact(content, redactors):
    """
    Replaces every substring in content that matches any of the regexes in redactors
    with "REDACTED".
    content: A string to redact.
    redactors: A list of regular expression strings.
    """
    REDACTION_STRING = "" # Actually just erase things we want to redact,
                          # because sometimes we want to redact things which
                          # appear nondeterministically.
    for pattern in redactors:
        content = re.sub(pattern, REDACTION_STRING, content)
    return content


PORTS_FILENAME = Path("chisel_oracle_ports.txt")

class OracleHelper:
    check_number = 0
    record = None

    def __init__(self, oracle_module_name):
        self.oracle_module_name = oracle_module_name

    def _known_good_filename(self):
        "Returns the filename of the known good value for the current check."
        return Path("/tmp") / self.oracle_module_name / str(OracleHelper.check_number)

    def check_or_record(self, testcase, data):
        """
        If recording, the check_number is used to create a file which
        contains the data.
        If not recording, the data is checked against the contents of the file
        that corresponds to the provided marker information.

        testcase: The testcase performing the assertion.
        data: The information to record, or to check against the known good value.
        This data is converted into yaml before recording, and converted from yaml
        before checking.
        """
        assert OracleHelper.record is not None, "Record must be set to true or false"
        filename = self._known_good_filename()
        if OracleHelper.record:
            dir = filename.parent
            dir.mkdir(parents=True, exist_ok=True)
            with open(filename, "x") as f:
                print("recording {}".format(filename))
                f.write(yaml.dump(data))
                OracleHelper.check_number += 1
        else:
            with open(filename, "r") as f:
                print("checking {}".format(filename))
                # Increment the check_number before making the assertion, so
                # that if it fails, the check number will be right for the
                # next test.
                OracleHelper.check_number += 1
                testcase.assertEqual(data, yaml.safe_load(f))

    @contextmanager
    def check_process(self, testcase, cmd, stdin="", shutdown=communicate,
                      ignore=[], redactors=[]):
        """
        Check the results of running the cmd against known good values.  stdout,
        stderr, and the process return code are checked.  If recording, then save
        the results of the process to a canonical location instead.

        LIMITATION: Your checks must run in a deterministic order across
        the test suite, and you must always run the entire test suite so that all
        checks take place.

        LIMITATION: Don't read from the process' stdout or stderr or that
        information won't get serialized when recording the process' results.

        cmd: A string representing the command to run.  The placeholder {sut} will
             be replaced by the binary under test.
        stdin_filename: A filename to open and read into the process's stdin.
        shutdown: A function that ends the process, which accepts a string
                  (the value meant to be given to stdin), and returns the 
                  process' stdout and stderr
        ignore: A list of string keys corresponding to attributes of the 
                completed process which will not be compared.
                The attributes which will be compared if this list is empty are:
                "cmd", "stdout", "stderr", "returncode"
        redactors: A list of regular expressions.  Any substring which matches 
                   any of the regexes will be replaced with the string REDACTED.
                   These redactors are applied to the stdout and stderr of the
                   process.
        """

        cmd = shlex.split(cmd)

        # Some of the benchmarks have support directories beside them, so
        # add the dirname to the LD_LIBRARY_PATH
        binary = cmd[0]
        dirname = os.path.dirname(binary)
        env = dict(os.environ)
        env["LD_LIBRARY_PATH"] = f"{dirname}:{env.get('LD_LIBRARY_PATH', '')}"

        print("process {}".format(cmd))
        proc = subprocess.Popen(
            cmd,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            stdin=subprocess.PIPE,
            text=True,
            env=env
        )

        try:
            yield proc
        finally:
            stdout, stderr = shutdown(proc, stdin)
            assert proc.returncode is not None
            data = {
                # Only serialize the args given to the command, since the
                # binary might have a different path while chisel runs.
                # Also redact the args, because sometimes we pass e.g. temporary
                # directories to the benchmarks
                "args": [redact(arg, redactors) for arg in cmd[1:]],
                "stdout": redact(stdout, redactors),
                "stderr": redact(stderr, redactors),
                "returncode": proc.returncode
            }
            for key in ignore:
                del data[key]
            print(f"checking process {cmd}")
            self.check_or_record(testcase, data)


#    def check_file(self, testcase, filename):
#        """
#        Check the contents of a file against known good values.  Filename should
#        be a relative path if the test is running in a temporary directory.
#
#        IMPORTANT LIMITATION: Your checks must run in a deterministic order across 
#        the test suite, and you must always run the entire test suite so that all
#        checks take place.
#        """
#        print("file {}".format(filename))
#        if type(filename) != Path:
#            filename = Path(filename)
#        with open(filename, 'rb') as f:
#            data = str((filename, f.read()))
#        self.check_or_record(testcase, data)

    def check_directory(self, testcase, directory, ignore=[], redactors=[]):
        """
        Records or checks the structure, file contents, and permissions of a directory
        tree.

        LIMITATION: See the limitations of the check_process function.

        testcase: The TestCase class using this helper function.
        directory: The path to the directory.
        ignore: File paths to ignore.
        redactors: See the explanation in check_process
        """
        print("directory {}".format(directory))
        dictionary = dir_tree_to_dict(directory, redactors)
        for key in ignore:
            if key in dictionary:
                del dictionary[key]
        print(f"checking directory {directory}")
        self.check_or_record(testcase, dictionary)

    def get_process_port(self, working_dir):
        """
        Get the port name, which is based off the current chisel working directory.
        """
        # If we're recording, we don't have to worry about multiple processes
        if self.record:
            return self.port_range[0]
        if re.search(r"\d+$", working_dir):
            offset = int(Path(working_dir).name)
            return self.port_range[offset]
        return self.port_range[0]


def positive_int(value):
    "Validate that a command line argument is a positive integer."
    ivalue = int(value)
    if ivalue <= 0:
        raise argparse.ArgumentTypeError(f"{value} is an invalid positive int value")
    return ivalue


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        prog="Chisel Oracle",
        description=(
            "Runs a test suite, either recording good values, or checking "
            "values against the recorded values."
        )
    )
    parser.add_argument("--record", action="store_true", help=(
        "Indicates that the oracle should record values."
    ))
    parser.add_argument("binary", type=Path, help=(
        "The path to the binary which the oracle tests."
    ))
    parser.add_argument("oracle_module", type=str, help=(
        "The oracle module to import, e.g. `medium.objdump.oracle_objdump_`.  "
        "It should contain a test class called Oracle."
    ))
    parser.add_argument("--port_start", type=int, help=(
        "The start of the port range which no other process but the oracles "
        "processes may use."
    ))
    parser.add_argument("--processes", type=positive_int, default=1, help=(
        "The number of oracle processes which will run simultaneously."
    ))
    args = parser.parse_args()

    # Inject test module parameters
    module = importlib.import_module(args.oracle_module)
    if args.binary.is_absolute():
        module.binary = args.binary
    else:
        module.binary = args.binary.absolute()
    module.OracleHelper.record = args.record
    if args.port_start is not None:
        if args.processes is None:
            print("You must specify both --port_start and --processes if your oracle needs to use a range of ports.", file=sys.stderr)
            exit(1)
        module.OracleHelper.port_range = list(range(args.port_start, args.port_start + 2 * args.processes))

    # Run tests
    test_class = getattr(module, "Oracle")
    runner = unittest.TextTestRunner(
        verbosity=2,
        failfast=True,
        stream=sys.stdout
    )
    suite = unittest.TestLoader().loadTestsFromTestCase(test_class)
    test_result = runner.run(suite)
    if not test_result.wasSuccessful():
        exit(1)
    exit(0)
