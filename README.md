# Workshop-VMImpl: Step 0 (Infrastructure) - Completed!
Welcome to my implementation of step 0! This will essentially be the same code as what's in the branch `step1begin`, but this document will be different (since the `step1begin` branch will contain the instructions for Step 1).

## Important Note: Tests
Note that both projects have unit tests in place already ***that will fail***, out of the box, right now. These are intended as very rough guides to make sure that your implementation meets our "expectations" (basically, that your code will work for future steps in the manner in which the workshop creator is expecting!). These are not considered to be extensive or comprehensive or even good examples of tests or TDD--they're just there to help make sure we're all on the same path together, and to give you a sense of what we're trying to build (in those situations where the text above isn't clear enough).

You are, of course, encouraged to add a few of your own, just to make sure that the code coverage is the industry-standard 110%!

## Steps
Our VirtualMachine needs some basic infrastructure to get started. Our VM will be an extremely simple stack-based machine, so as to keep the infrastructure needs lightweight and straightforward. We will begin by working solely wth integers (no floats, no strings, no booleans, etc) for both our bytecode operands and parameters.

### Some diagnostic options
In this step, you add a few properties and methods to make it easier to diagnose/debug the virtual machine itself.

* When we execute code, we'll want to keep track of our location through the code; define a field called `ip` (for "Instruction Pointer") that will keep track of where we are inside the currently-executing bytecode program.
* For a stack-based virtual machine, we obviously need a stack! Create an array of 100 integers and call it `stack`. We will also need to know where we are in this array (where is the top of the stack), so also create a "stack pointer" integer field, and call it `sp`.
* We will want (for both internal consistency and external testing purposes) easy ways to push and pop things from this stack. Implement a `push` / `Push` method that pushes something onto the `stack`. Likewise, `pop` / `Pop` will remove an element from the `stack` and return that value to the caller. Make sure both methods increment/decrement `sp` correctly.
    > **Implementation note:** Typically, a stack "grows downward" in memory, but when we have a flat array of integers, that perspective may or may not make sense. I typically view it this way: the first element pushed is at `stack[0]`, the second at `stack[1]`, and so on. I've had some people tell me that's "growing downwards", while others see it as "growing upwards". The terminology isn't important, but being consistent with the treatment of the stack pointer (`sp`) is critical. Fortunately, consistency is easily verified with unit tests, which is why we have them!
* Purely for our own testing purposes, provide a method (`getStack()`) or property (`Stack`) that returns a read-only copy of the current stack. *Make sure you only copy up to `sp`!* In other words, `getStack().length` or `Stack.Length` should return only those parts of `stack` that currently hold values pushed onto the stack.
* Implement a `dump` / `Dump` method on the VirtualMachine that will write to the console the current state of the virtual machine. It should not change the state of the virtual machine itself.
* *(Optional)* Add a boolean "trace" flag/property, defaulting to `false`. Use this flag to determine whether to print/log the various things going on in the VM. If you do this, also define a method (usually called "trace") that will print out a message passed in if the "trace" flag is set to `true`. This would be useful for logging-type statements from within the VM.

> **Implementation question:** What do you want to have happen when a caller `pop()`s with nothing remaining on the stack? This is typically a fatal error for a virtual machine, and could thus be represented with an exception thrown, but you may have opinions of your own what to do here.

### The core execute loop
In this step, you add the core fetch-decode-execute functionality that drives the heart of the virtual machine.

* Create a method called `execute` / `Execute` that takes a single Bytecode parameter, and a second parameter that allows for a variable list of integer parameters. (In Java, this is an `...`-suffixed declaration; in C#, use `params`.) Within this method, you will examine the incoming opcode to determine what to execute--this is traditionally a giant "switch" statement. Thus far, since we have no bytecode implemented yet, it will be empty.

### The first bytecode: NOP
In this step, you add the first bytecode operation, the one that does... nothing.

* Implement the world's simplest opcode: `NOP`, which literally does nothing. Create an enumeration type (or its closest equivalent) called `Bytecode`. Within that enumeration, define `NOP` as a value. (If the enumerations are backed by integers, set `NOP` to be `0`, which is its traditional value.) In your `execute` method, have the `NOP` branch of your switch do nothing. (You may want to "trace" that you've done nothing, just to make sure that your switch is working correctly.) `NOP` has no parameters, so either ignore any parameters passed in, or if you want to be really defensive about it, "trace" that parameters were passed in and ignored.

> **Implementation note: Bytecode operation values.** It is not uncommon for instructions to be "grouped" into particular ranges, so that all of the "diagnostic" bytecodes might be the numeric values 0 to 9, the "stack" instructions 10 to 19, the "maths" operations 20 to 29, and so on. These numbers are opaque to us in this workshop, but in production implementations they are often grouped this way in order to "pack" instructions and parameters into a single 32- or 64-bit value via bit manipulation. Just keep in mind that once you put your virtual machine into production, you cannot ever go back and rearrange the instruction values!

### The diagnostic bytecode: DUMP and TRACE
*(This is an optional step.)*

* Implement a `TRACE` bytecode, whose implementation is to "flip" the "trace" flag (if you implemented it) to `true` if it's currently `false`, and vice-versa.
* Implement a `DUMP` bytecode, whose implementation is to call your VirtualMachine's `dump`/`Dump` method.
* Implement a `FATAL` bytecode, which terminates the VM immediately (throw an exception that's not intended to be caught by callers). This is often useful during testing to immediately spot errors.

### The stack bytecodes: CONST (push) and POP
The next bytecode is `POP`, which removes the top of the stack.

* Implement a `POP` opcode, which takes no parameters ("operands") and simply pops off the current top of the stack. (It mimics the `pop`/`Pop` method, basically.)

* Create another `execute`/`Execute` method called that takes an array of `Bytecode` values. This array will contain a stream of (essentially) integer values, a mix of operations and their operands. This new, overloaded, "execute" method will take the array of `Bytecode`, set the "instruction pointer" to 0, and examine the bytecode at the 0th position in the array. If it is a bytecode that expects an argument/operand, it will need to grab the next element in the array (incrementing IP appropriately!) and pass it as the parameter when calling the original `execute`/`Execute` method.

* Implement a `CONST` opcode, which expects one parameter. Inside of "execute", push that parameter onto the stack. (In other words, `CONST 14` will be the same as calling `pop(14)` / `Pop(14)`.)

* Implement a `PRINT` opcode, which expects one parameter. Print that paramter to the console.

### Make sure all the tests pass!
And implement a few more if you want or need.
