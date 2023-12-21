from chisel_oracle import OracleHelper, finish, terminate
import os
import tempfile
import unittest
import shutil
from contextlib import contextmanager, ExitStack

binary = "[no binary specified]"
oracle = OracleHelper(__name__.replace("oracle_", ""))


def transform_file(src, dest, replacements=dict()):
    with open(src, 'r') as input:
        with open(dest, 'w') as output:
            data = input.read()
            for to_replace, replacement in replacements.items():
                data = data.replace(to_replace, replacement)
            output.write(data)


@contextmanager
def bftpd(testcase, args):
    cm = ExitStack()
    port = oracle.get_process_port(testcase.prior_dir)
    try:
        replacements = {
            "{{trace.cwd}}": os.getcwd(),
            "PORT=\"8021\"": f"PORT=\"{port}\""
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
        cm.enter_context(
            oracle.check_process(testcase, f"{binary} {args}", shutdown=terminate)
        )
        yield port
    finally:
        cm.close()


def lftp(testcase, port, *cmds):
    print(f"Using port {port}!!!")
    transform_file(
        "/input_files/lftp.rc",
        "lftp.rc",
        {
            "-p 8021": f"-p {port}"
        }
    )
    cmds = "\n".join(cmds + ("exit",))
    finish(oracle.check_process(
        testcase,
        "lftp --rc lftp.rc",
        stdin=cmds,
        redactors=[
            r"127\.0\.0\.1:\d+",
        ]
    ))


def put_file(name, contents):
    with open(name, 'w') as handle:
        handle.write(contents)


class Oracle(unittest.TestCase):
    def setUp(self):
        self.dir = tempfile.mkdtemp()
        self.prior_dir = os.getcwd()
        self.maxDiff = None
        self.dir_redactors = [
            # Datetime
            r"\w{3} \w{3} [ \d]\d (\d\d:){2}\d\d \d\d\d\d",
            # The following pattern appears after the binary in the log, and I
            # think it represents the process ID
            r"{}\[\d+\]:".format(os.path.basename(binary)),
            # Temporary directory
            r"/tmp/tmp[A-Za-z0-9_]+/",
            # Port numbers
            r"PORT=\"\d+\"",
            r"open -p \d+",
        ]
        self.ignore = [
            "./bftpd.log",
        ]
        os.chdir(self.dir)
        shutil.copytree("/input_files/bftpd-serve", "serve")
        shutil.copy("/input_files/lftp.rc", "lftp.rc")

    def tearDown(self):
        os.chdir(self.prior_dir)
        shutil.rmtree(self.dir)

    def test_get_file(self):
        assert not os.path.isfile("file.txt")
        with bftpd(self, "-D -c default-anon.conf") as port:
            lftp(self, port, "get file.txt")
        oracle.check_directory(
            self,
            ".",
            redactors=self.dir_redactors,
            ignore=self.ignore
        )

    def test_navigate(self):
        with bftpd(self, "-D -c default-anon.conf") as port:
            lftp(
                self,
                port,
                "ls",
                "cd child",
                "ls",
                "cd ..",
                "ls",
            )
        oracle.check_directory(
            self,
            ".",
            redactors=self.dir_redactors,
            ignore=self.ignore
        )

    def test_chmod(self):
        os.chmod("serve/file.txt", 0o444)
        with bftpd(self, "-D -c default-anon.conf") as port:
            lftp(
                self,
                port,
                "chmod 440 file.txt"
            )
        oracle.check_directory(
            self,
            ".",
            redactors=self.dir_redactors,
            ignore=self.ignore
        )

    def test_put(self):
        put_file("file", "hello world")
        self.assertFalse(os.path.isfile("serve/file"))
        with bftpd(self, "-D -c default-anon.conf") as port:
            lftp(
                self,
                port,
                "put file"
            )
        oracle.check_directory(
            self,
            ".",
            redactors=self.dir_redactors,
            ignore=self.ignore
        )

    def test_mkdir(self):
        self.assertFalse(os.path.isdir("serve/second"))
        with bftpd(self, "-D -c default-anon.conf") as port:
            lftp(
                self,
                port,
                "mkdir second"
            )
        oracle.check_directory(
            self,
            ".",
            redactors=self.dir_redactors,
            ignore=self.ignore
        )

    def test_mv(self):
        self.assertFalse(os.path.isfile("server/file2.txt"))
        with bftpd(self, "-D -c default-anon.conf") as port:
            lftp(
                self,
                port,
                "mv file.txt file2.txt"
            )
        oracle.check_directory(
            self,
            ".",
            redactors=self.dir_redactors,
            ignore=self.ignore
        )

    def test_pwd(self):
        with bftpd(self, "-D -c default-anon.conf") as port:
            lftp(
                self,
                port,
                "cd ..",
                "cd ..",
                "pwd"
            )
        oracle.check_directory(
            self,
            ".",
            redactors=self.dir_redactors,
            ignore=self.ignore
        )

    def test_rm(self):
        assert os.path.isfile("serve/file.txt")
        with bftpd(self, "-D -c default-anon.conf") as port:
            lftp(
                self,
                port,
                "rm file.txt"
            )
        oracle.check_directory(
            self,
            ".",
            redactors=self.dir_redactors,
            ignore=self.ignore
        )

    def test_rmdir(self):
        os.mkdir("serve/delete_me")
        with bftpd(self, "-D -c default-anon.conf") as port:
            lftp(
                self,
                port,
                "rmdir delete_me",
            )
        oracle.check_directory(
            self,
            ".",
            redactors=self.dir_redactors,
            ignore=self.ignore
        )

    # Disabled commands
    def test_rm_disabled(self):
        with bftpd(self, "-D -c disabled-cmds-anon.conf") as port:
            lftp(
                self,
                port,
                "rm file.txt"
            )
        oracle.check_directory(
            self,
            ".",
            redactors=self.dir_redactors,
            ignore=self.ignore
        )

    def test_rmdir_disabled(self):
        os.mkdir("serve/delete_me")
        with bftpd(self, "-D -c disabled-cmds-anon.conf") as port:
            lftp(
                self,
                port,
                "rmdir delete_me",
            )
        oracle.check_directory(
            self,
            ".",
            redactors=self.dir_redactors,
            ignore=self.ignore
        )

    def test_chmod_disabled(self):
        with bftpd(self, "-D -c disabled-cmds-anon.conf") as port:
            lftp(
                self,
                port,
                "chmod 440 file.txt"
            )
        oracle.check_directory(
            self,
            ".",
            redactors=self.dir_redactors,
            ignore=self.ignore
        )

    def test_put_disabled(self):
        put_file("file", "hello world")
        with bftpd(self, "-D -c disabled-cmds-anon.conf") as port:
            lftp(
                self,
                port,
                "put file"
            )
        oracle.check_directory(
            self,
            ".",
            redactors=self.dir_redactors,
            ignore=self.ignore
        )

    def test_no_args(self):
        finish(oracle.check_process(self, f"{binary}"))

    def test_help(self):
        finish(oracle.check_process(
            self,
            f"{binary} -help",
            redactors=[
                # Text can be wrapped different way depending on the length of
                # the path.
                "\n",
                # The help text prints the absolute path to the binary
                "/.*/?bftpd",
            ]
        ))
