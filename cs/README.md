# SimpleVM: C# Implementation
This directory contains the C# implementation of the SimpleVM stack-machine implementation.

Given that this is greenfield work, the project uses latest-and-greatest versions of `dotnet` at the time of its creation. Currently that means:

* .NET SDK v6.0.300

The root SLN file contains references to the `vm` project, which is the virtual machine implementation project. Tests for `vm` are found in the peer `vmtest` project, and `app` doesn't do much besides provide a simple shell by which to run the VM, for those who prefer to see console output instead of test results.

## Running tests
`dotnet test` from the top-level directory will run the `vmtest` tests. There are no `app` tests.

If you use `Console.WriteLine` to display output, the standard test runner will not display it; to see the generated console messages, use `dotnet test -l "console;verbosity=detailed"` instead.

## Running the app
`dotnet run --project app` from the top-level directory will run the app, or drop into the `app` directory and do a `dotnet run` from there.

