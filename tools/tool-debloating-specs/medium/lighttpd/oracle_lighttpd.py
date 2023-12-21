from chisel_oracle import OracleHelper, finish, terminate
import tempfile
import os
import shutil
import unittest
from contextlib import contextmanager


binary = "[no binary specified]"
oracle = OracleHelper(__name__.replace("oracle_", ""))
wget_redactors = [
    r"\d+\.\d+ MB/s", # Transfer rate
    r"\d+ [KMG]B\/s",
    r"\d\d:\d\d:\d\d", # Transfer time
    r"\d+\.?\d*[KM]=\d+s", # Transfer rate and time
    r"100%  ?", # Sometimes an extra space appears after 100% for some reason.
    r"\d{4}-\d\d-\d\d", # Dates
    r":\d+", # Port numbers
]

lighttpd_redactors = [
    r"\d{4}-\d\d-\d\d", # Dates
    r"(\d\d:){3}", # Times
    r"PID = \d+", # Process IDs
]

file_redactors = [
    r"/tmp/tmp[^/\s\\]+", # The temporary directory
    r"server.port = \d+", # The port
]


@contextmanager
def lighttpd(testcase, cmd):
    conf_files = [
        "/input_files/lighttpd-static-all.conf",
        "/input_files/lighttpd-static-exclude-php.conf",
        "/input_files/lighttpd-static-index.conf",
        "/input_files/lighttpd-static-vhost.conf",
    ]
    port = oracle.get_process_port(testcase.prior_dir)
    replacements = {
        "{{trace.cwd}}": testcase.dir,
        "server.port = 3000": f"server.port = {port}",
    }
    for conf in conf_files:
        transform_file(
            conf,
            conf.replace("/input_files/lighttpd-", ""),
            replacements
        )
    context = oracle.check_process(
        testcase,
        str(binary) + " " + cmd,
        shutdown=terminate,
        redactors=lighttpd_redactors
    )
    context.__enter__()
    try:
        yield port
    finally:
        context.__exit__(None, None, None)


def wget(testcase, args):
    finish(oracle.check_process(
        testcase,
        "wget " + args,
        redactors=wget_redactors
    ))


def transform_file(src, dest, replacements=dict()):
    with open(src, 'r') as input:
        with open(dest, 'w') as output:
            data = input.read()
            for to_replace, replacement in replacements.items():
                data = data.replace(to_replace, replacement)
            output.write(data)

def put_file(filename, content):
    os.makedirs(os.path.dirname(filename), exist_ok=True)
    with open(filename, 'w') as f:
        f.write(content)


class Oracle(unittest.TestCase):
    def setUp(self):
        self.dir = tempfile.mkdtemp()
        self.prior_dir = os.getcwd()
        self.maxDiff = None
        os.chdir(self.dir)
        put_file("serve-vhost/hello.text", "hello world")
        shutil.copytree("/input_files/lighttpd-serve", "serve")

    def tearDown(self):
        os.chdir(self.prior_dir)
        shutil.rmtree(self.dir)

    def test_get_root_file(self):
        with lighttpd(self, "-D -f static-all.conf") as port:
            wget(self, f"http://localhost:{port}/index.html")
        oracle.check_directory(self, ".", redactors=file_redactors)

    def test_get_nested_file(self):
        with lighttpd(self, "-D -f static-all.conf") as port:
            wget(self, f"http://localhost:{port}/dir1/file1.html")
        oracle.check_directory(self, ".", redactors=file_redactors)

    def test_get_index(self):
        with lighttpd(self, "-D -f static-index.conf") as port:
            wget(self, f"http://localhost:{port}")
        oracle.check_directory(self, ".", redactors=file_redactors)

    def test_get_include_ext(self):
        with lighttpd(self, "-D -f static-exclude-php.conf") as port:
            wget(self, f"http://localhost:{port}/index.html")
        oracle.check_directory(self, ".", redactors=file_redactors)

    def test_get_exclude_ext(self):
        with lighttpd(self, "-D -f static-exclude-php.conf") as port:
            wget(self, f"http://localhost:{port}/run.php")
        oracle.check_directory(self, ".", redactors=file_redactors)

    def test_get_vhost_1(self):
        with lighttpd(self, "-D -f static-vhost.conf") as port:
            wget(self, f"http://127.0.0.1:{port}/index.html")
        oracle.check_directory(self, ".", redactors=file_redactors)

    def test_get_vhost_2(self):
        with lighttpd(self, "-D -f static-vhost.conf") as port:
            wget(self, f"http://127.0.0.1:{port}/hello.txt")
        oracle.check_directory(self, ".", redactors=file_redactors)

    def test_get_vhost_3(self):
        with lighttpd(self, "-D -f static-vhost.conf") as port:
            wget(self, f"http://127.0.1.1:{port}/hello.txt")
        oracle.check_directory(self, ".", redactors=file_redactors)

    def test_get_404(self):
        with lighttpd(self, "-D -f static-all.conf") as port:
            wget(self, f"http://localhost:{port}/foo.html")
        oracle.check_directory(self, ".", redactors=file_redactors)

    def test_no_args(self):
        finish(oracle.check_process(self, f"{binary}", redactors=lighttpd_redactors))

    def test_help(self):
        finish(oracle.check_process(self, f"{binary} -help", redactors=lighttpd_redactors))
