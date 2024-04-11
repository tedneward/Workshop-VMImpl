# SimpleVM: Python implementation
This directory contains the Python implementation of the SimpleVM stack-machine implementation.

Given that this is greenfield work, the project uses latest-and-greatest versions of Python at the time of its creation. Currently that means:

* Python 3.12

All of the code defining the virtual machine is in the `simplevm` package, which already has an `init.py` in it to ensure Python treats it as a package as per the usual Pythonic rules.

## Running tests
The tests in the `tests` directory make use of the standard Python `unittest` package. You can run all the tests using `python3 -m unittest` from the top directory (where you find this README), and you can see a verbose run of the tests by adding a `-v` to the end of the command line. Alternatively, you can run a single test case suite using `python3 -m tests.test_calls` (to run the tests defined in the `test_calls.py` file), if you just want to run a single test suite. (Generally, I think it's best to run all of them together, as a constant regression test, but hey, you do you.)

## Running the app
The `app.py` is the "application" for executing the virtual machine, but it defers all work to the `VirtualMachine` class defined in the `simplevm` directory/package.
