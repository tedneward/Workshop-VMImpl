# Workshop-VMImpl
Files and templates to go along with my "Busy Dev's Workshop on Building a Virtual Machine"

Because this workshop is intended for developers of all stripes, there are several subdirectories here with implementation scaffolding for different language/platforms:

* C#
* Java

(In the future I plan to add C++, Python, JavaScript or TypeScript, Swift, Kotlin, F#, and maybe Ruby. Other possibilities are swimming in my brain, but those are the ones I know I really want to have as options here.) 

Developers are free to choose whichever of the subdirectories they wish. Alternatively, if comfortable with doing so, feel free to create a new subdirectory and implement it in your own language of choice. Virtual machines have been written in almost every language in the universe, including Smalltalk and JavaScript and Self, and the concepts we are exploring here are not so low-level that performance or overhead will be a problem.

## C#
There is a .NET Core project set up to use C# to implement the Workshop in the `cs` subdirectory from here. See that README for details.

## Java
There is a Gradle project set up to use Java to implement the Workshop in the `java` subdirectory from here. See that README for details.

## App vs VM
Note that all of the projects are set up in an "app"/"lib" structure, where the VM is built as a library, called from a very simple shell called "app". We won't actually use "app" for anything in this workshop, and it is provided merely as an extension point should you wish to try running the VM from the command-line.

# Steps
The steps to the workshop are as follows:

* **Step 0: Infrastructure**: Our virtual machine needs some basic infrastructure to get started, such as a stack, an instruction pointer, and the ability to push and pop elements from the stack. We'll also introduce a few "diagnostic" and stack-support bytecode instructions to make it easier for us to debug/diagnose both the virtual machine and our bytecode programs as we go.
* **Step 1: Maths**: Having created a simple stack VM, let's add some basic calculation functionality. This will require introducing some bytecode instructions to do the canonical maths operations (add, subtract, etc).
* **Step 2: Comparisons**: Very similar to the mathematical operators, comparison operators compare two values and return either a "true" or "false" result to the top of the stack.
* **Step 3: Jumping and Branching**: Programs often need to change their next execution location from the "next" address to one elsewhere in the code stream, often as the result of a comparison operator. (This is what happens when you write an `if`/`else` branch in code, after all.) So we need to implement a set of "execution modification" bytecode instructions.
* **Step 4: Global variable storage**: Being able to do all these wonderful calculations and decisions doesn't add up to much if we can't store results in some kind of location for later reference. So let's implement some global storage bytecode instructions.
* **Step 5: Procedures and local variable storage**: The last "reasonable" feature our virtual machine needs is the ability to create a local storage space for non-global storage that will be automatically reclaimed when we are finished. We often call these "procedures", and it's not uncommon for a virtual machine to have direct support for them.

Some optional steps to consider adding to your virtual machine:

* **Additional numeric types**: Many platforms differentiate between 8-, 16-, 32-, 64-, and 128-bit values. (Some go even larger.) Without changing the fundamental structure of the VirtualMachine as it exists now, how would you add support for those types?
* **String (and Character) types**: Currently the machine only supports integers natively, but if we think about integers as being the "word-sized values" that all CPUs natively support, we can imagine how we might support strings. Of course, this then means some radical refactoring of the bytecode implementations, since `ADD`ing two strings means something very different than `ADD`ing two numbers. This often begs the question of whether strings should be treated natively by the VM (as the JVM and CLR do, sort of), or whether they should be treated at "user-level" (the way C/C++ does).
* **Type safety**: What happens if we try to add an integer value to a string? What happens when we try to add an integer value to a floating-point value? What *should* happen? More importantly, where and how do we track the type information of a given piece of data, so that we know what it is we're adding (or subtracting or dividing or ...)?
* **Disk format**: Right now all the bytecode we execute is stored as a part of the tests we're writing; a more reasonable virtual machine would have the ability to execute files that contain our bytecode. What sort of file format would offer forward-compatibility with new features we might add to the VM, while still being able to execute "v1" bytecode scripts we might write today?

If you're ready to get started, do a `git checkout step0begin` and have at it! Keep in mind that you can always check your work against my implementation (on the `step0end` branch).
