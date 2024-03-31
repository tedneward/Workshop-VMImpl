# Workshop-VMImpl
Files and templates to go along with my "Busy Dev's Workshop on Building a Virtual Machine"

Because this workshop is intended for developers of all stripes, there are several subdirectories here with implementation scaffolding for different language/platforms:

* C#
* Java

Developers are free to choose whichever of the subdirectories they wish. Alternatively, if comfortable with doing so, feel free to create a new subdirectory and implement it in your own language of choice. Virtual machines have been written in almost every language in the universe, including Smalltalk and JavaScript and Self, and the concepts we are exploring here are not so low-level that performance or overhead will be a problem.

## C#
There is a dotnet 6.0 proejct set up to use C# to implement the Workshop in the `cs` subdirectory from here. See that README for details.

## Java
There is a Gradle project set up to use Java to implement the Workshop in the `java` subdirectory from here. See that README for details.

## App vs VM
Note that all of the projects are set up in an "app"/"lib" structure, where the VM is built as a library, called from a very simple shell called "app". We won't actually use "app" for anything in this workshop, and it is provided merely as an extension point should you wish to try running the VM from the command-line.

# Steps
The steps to the workshop are as follows:

* **Step 0: Infrastructure**: Our virtual machine needs some basic infrastructure to get started, such as a stack, an instruction pointer, and the ability to push and pop elements from the stack. We'll also introduce a few "diagnotic" bytecode instructions to make it easier for us to debug/diagnose both the virtual machine and our bytecode programs as we go.
* **Step 1: Maths**: Having created a simple stack VM, let's add some basic calculation functionality. This will require introducing some bytecode instructions to push literal values onto the stack, as well as some bytecode instructions to do the canonical maths operations (add, subtract, etc).
* **Step 2: **:
* **Step 3: **:
* **Step 4: **:

Some optional steps to consider adding to your virtual machine:

If you're ready to get started, do a `git checkout step0begin` and have at it! Keep in mind that you can always check your work against my implementation (on the `step0end` branch).
