from chisel_oracle import OracleHelper, finish, terminate
import os
import tempfile
import unittest
import shutil
import subprocess
from contextlib import contextmanager
import shlex

binary = "[no binary specified]"
oracle = OracleHelper(__name__.replace("oracle_", ""))


def transform_file(src, dest, replacements=dict()):
    with open(src, 'r') as input:
        with open(dest, 'w') as output:
            data = input.read()
            for to_replace, replacement in replacements.items():
                data = data.replace(to_replace, replacement)
            output.write(data)


def wget(testcase, args):
    assert type(args) == str
    finish(oracle.check_process(
        testcase,
        "wget " + args,
        redactors=[
            r"\d+\.\d+ MB/s", # Transfer rate
            r"\d+ [KMG]B\/s",
            r"\d\d\d\d-\d\d-\d\d \d\d:\d\d:\d\d", # Transfer datetime
            r"\d+\.?\d*[KM]=\d+s", # Transfer rate and time
            r"(\d{1,3}\.){3}\d{1,3}:\d+", # IP addresses and ports
            r"([a-f\d]{1,4}:){3}[a-f\d]{1,4}::[a-f\d]{1,4}",
            r"100%  ?", # Sometimes an extra space appears after 100% for some reason.
        ]
    ))


@contextmanager
def nginx(testcase, args):
    port = oracle.get_process_port(testcase.prior_dir)
    transform_file(
        "/input_files/nginx-file_server.conf",
        "file_server.conf",
        {
            "listen 8080;": f"listen {port};"
        }
    )
    cm = oracle.check_process(
        testcase,
        f"{binary} {args}",
        shutdown=terminate,
        redactors=[
            "/tmp/tmp[a-zA-Z0-9_]+"
        ]
    )
    try:
        cm.__enter__()        
        yield port
    finally:
        cm.__exit__(None, None, None)


class Oracle(unittest.TestCase):
    def setUp(self):
        self.dir = tempfile.mkdtemp()
        self.prior_dir = os.getcwd()
        self.maxDiff = None
        self.file_redactors = [
            # Time stamps
            r"\d\d/\w+/\d\d\d\d:\d\d:\d\d:\d\d",
            r"\d\d\d\d/\d\d/\d\d \d\d:\d\d:\d\d",
            # Process ID
            r"\[error\] \d+#0",
            # Temporary directory
            r"/tmp/tmp[a-zA-Z0-9_]+",
            # Port
            r"listen \d+;",
            r"127.0.0.1:\d+",
        ]
        os.chdir(self.dir)
        os.mkdir("logs")
        shutil.copytree("/input_files/nginx-serve-ip", "serve-ip")
        os.chmod(self.dir, 777)
        for root, dirs, files in os.walk(self.dir):
            for dir in dirs:
                os.chmod(os.path.join(root, dir), 0o0777)
            for file in files:
                os.chmod(os.path.join(root, file), 0o0777)
        

    def tearDown(self):
        os.chdir(self.prior_dir)
#        shutil.rmtree(self.dir)

    def test_file_server_download(self):
        with nginx(self, f"-p {os.getcwd()} -c file_server.conf") as port:
            wget(self, f"http://127.0.0.1:{port}/dir1/file1.html")
            wget(self, f"http://127.0.0.1:{port}/dir1/./../about.html")
            wget(self, f"-O index.html http://127.0.0.1:{port}")
        oracle.check_directory(self, ".", redactors=self.file_redactors)

    def test_file_server_download_404(self):
        with nginx(self, f"-p {os.getcwd()} -c file_server.conf") as port:
            wget(self, f"http://127.0.0.1:{port}/dir2/about.html")
        oracle.check_directory(self, ".", redactors=self.file_redactors)
