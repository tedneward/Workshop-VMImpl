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

# Steps
The steps to the workshop are as follows:

## Step 0: Infrastructure
Our VirtualMachine needs some basic infrastructure to get started. Our VM will be an extremely simple stack-based machine, so as to keep the infrastructure needs lightweight and straightforward. We will begin by working solely wth integers (no floats, no strings, no booleans, etc).

* *(Optional)* Add a boolean "trace" flag/property, defaulting to `false`. Use this flag to determine whether to print/log the various things going on in the VM. 
* We want to begin by implementing the world's simplest opcode: `NOP`, which literally does nothing. Create an enumeration type (or its closest equivalent) called `Bytecode`. Within that enumeration, define `NOP` as a value. (If the enumerations are backed by integers, set `NOP` to be `0`, which is its traditional value.)
* When we execute code, we'll want to keep track of our location through the code; define a field called `IP` (for "Instruction Pointer") that will keep track of where we are inside the bytecode.
* The VM needs our processor loop; create a method called `execute`/`Execute` that takes an array of `Bytecode` values. Within this method, walk through the array, and if the bytecode value is a `NOP`, do nothing. (Put a comment there, just as a reminder that this is deliberate!) If it is an unrecognized value, throw an exception that states as much. Make sure `IP` is pointing to the current location in the bytecode at all times!



