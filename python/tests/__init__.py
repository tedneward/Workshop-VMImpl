import unittest

from simplevm.vm import VirtualMachine

class SimpleTests(unittest.TestCase):
    """A barebones test case to make sure unit tests are working."""

    def test_math(self):
        self.assertEqual(2 + 2, 4, 'The sum is wrong.')

    # Uncomment this to make sure failing tests actually fail!
    #def test_fail(self):
    #    self.assertEqual(2 - 2, 4, 'The sum is wrong.')
