# SimpleVM: Java implementation
This directory contains the Java implementation of the SimpleVM stack-machine implementation.

Given that this is greenfield work, the project uses latest-and-greatest versions of Java at the time of its creation. Currently that means:

* Gradle 7.4.2
* Java 18

The root Gradle settings.gradle.kts contains references to the `vm` project, which is the virtual machine implementation project. Tests for `vm` are found in that project, and the peer `app` project doesn't do much besides provide a simple shell by which to run the VM, for those who prefer to see console output instead of test results.

## Running tests
`gradle test` from the top-level directory, or drop into `vm` and `gradle test` from there (which is slightly faster). There are no `app` tests as of this writing.

## Running the app
`gradle run` from the top-level directory, or drop into `app` and `gradle run` from there.

