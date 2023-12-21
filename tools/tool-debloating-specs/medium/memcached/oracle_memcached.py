from chisel_oracle import OracleHelper, finish, terminate
import time
import tempfile
import os
import shutil
import unittest
from contextlib import contextmanager
from pymemcache.client import base

binary = "[no binary specified]"
oracle = OracleHelper(__name__.replace("oracle_", ""))


@contextmanager
def memcached(testcase):
    port = oracle.get_process_port(testcase.prior_dir)
    context = oracle.check_process(
        testcase,
        f"{binary} -u memcached -p {port}",
        shutdown=terminate,
        ignore=[
            "args"
        ]
    )
    client = base.Client(
        f"127.0.0.1:{port}",
        default_noreply=False
    )
    context.__enter__()
    time.sleep(0.5)
    try:
        yield client
    finally:
        context.__exit__(None, None, None)


class Oracle(unittest.TestCase):
    def setUp(self):
        self.maxDiff = None
        self.dir = tempfile.mkdtemp()
        self.prior_dir = os.getcwd()
        os.chdir(self.dir)

    def tearDown(self):
        os.chdir(self.prior_dir)
        shutil.rmtree(self.dir)

    def test_set_get(self):
        with memcached(self) as client:
            self.assertTrue(client.set('a', '10'))
            self.assertEqual(client.get('a'), b'10')
            # test_set_expiration_get_expired
            self.assertTrue(client.set('b', '10', expire=2))
            self.assertEqual(client.get('b'), b'10')
            time.sleep(3.0)
            self.assertIsNone(client.get('b'))
            # test_add
            self.assertTrue(client.add('c', '10'), True)
            self.assertEqual(client.get('c'), b'10')
            # test_add_exists
            self.assertTrue(client.set('d', '10'))
            self.assertFalse(client.add('d', '20'))
            self.assertEqual(client.get('d'), b'10')
            # test_replace
            self.assertTrue(client.add('e', '10'))
            self.assertTrue(client.replace('e', '20'))
            # test_replace_nonexistent
            self.assertFalse(client.replace('f', '10'))
            # test_append
            self.assertTrue(client.add('g', '10'))
            self.assertTrue(client.append('g', '10'))
            self.assertEqual(client.get('g'), b'1010')
            # test_append_nonexistent
            self.assertFalse(client.append('h', '10'))
            # test_prepend
            self.assertTrue(client.add('i', '10'))
            self.assertTrue(client.prepend('i', '00'))
            self.assertEqual(client.get('i'), b'0010')
            # test_prepend_nonexistent
            self.assertFalse(client.prepend('j', '00'))
            self.assertFalse(client.get('j'))
            # test_delete
            self.assertTrue(client.add('k', '10'))
            self.assertTrue(client.delete('k'))
            self.assertFalse(client.get('k'))
            # test_delete_nonexistent
            self.assertFalse(client.get('l'))
            self.assertFalse(client.delete('l'))
            self.assertFalse(client.get('l'))
            # test_incr
            self.assertTrue(client.set('m', '10'))
            self.assertTrue(client.incr('m', 1))
            self.assertEqual(client.get('m'), b'11')
            # test_incr_nonexistent
            self.assertFalse(client.get('n'))
            self.assertFalse(client.incr('n', 1))
            self.assertFalse(client.get('n'))
            # test_decr
            self.assertTrue(client.set('o', '10'))
            self.assertTrue(client.decr('o', 1))
            # This is actually returning b'9 ', so we do a comparison that
            # ignores whitespace.  We care that the result is 9 with possible
            # whitespace, not that we necessarily want the whitespace there.
            self.assertEqual(
                str(client.get('o'), encoding='utf-8').strip(),
                '9'
            )
            # test_decr_nonexistent
            self.assertFalse(client.get('p'))
            self.assertFalse(client.decr('p', 1))
            self.assertFalse(client.get('p'))

    def test_no_args(self):
        finish(oracle.check_process(self, f"{binary}", shutdown=terminate))

    def test_help(self):
        finish(oracle.check_process(self, f"{binary} --help"))
