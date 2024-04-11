import unittest

from simplevm import VirtualMachine

class BarebonesVMTests(unittest.TestCase):
    """A barebones test case to make sure unit tests are working."""

    def setUp(self):
        self.vm = VirtualMachine()

    def test_vmalloc(self):
        self.assertIsNotNone(self.vm, "The VM failed to allocate")

    def tearDown(self):
        self.vm = None
