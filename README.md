# Workshop-VMImpl: Step 5 (Procedures and Locals) - Completed!
Welcome to my implementation of step 5!

## Implementation notes


## Further work
You may want to consider some additional implementation work, just for fun:

### CALL-Indirect
Add a CALLI opcode that takes the index to call from the top of the operand stack, rather than from the next value in the bytecode. (This would be how we would implement invocation through a pointer at runtime, rather than a known value at the time the code was compiled, so as to implement dynamic dispatch of methods and inheritance, for example.)

### Top-level CallFrame
It would be an interesting exercise to implement in the `VirtualMachine` the assumption that there is always at least one `CallFrame` active; that is to say, when we call `execute(int[])`, we create a `CallFrame` in which to execute that code. This would also give us locals support at the top-most level of code execution. That in turn could spark some discussion as to whether we need "globals" when we have "locals" at this topmost level.

However, doing this requires that we always be keeping an eye on the returnAddress of any `CallFrame`, because if that points to -1 (or some other signal), it indicates we are at the topmost level of the call stack, and there's no place to return to. Or, rather, returning from the topmost `CallFrame` should terminate the `VirtualMachine` entirely, just like returning from `main` does in a C-family-language program.

### Add Strings
Strings are really just a sequence of integer values (ASCII and Unicode are both "encodings" of how a human alphabet should be rendered in binary values), so adding first-class String support to our VM would be relatively easy, but widespread. You'd need to:

* figure out what a String representation looks like in the VM. (C, for example, considers a String to be a sequence of 8-bit values that are eventually terminated by a "0" value.)
* figure out what a String on the operand stack looks like. In most implementations, it'll be an address to an array of values, but you'll need to differentiate (somehow) between `CONST 12` and `CONST "Hello world"` that happens to sit at location 12 somewhere in memory. Some VMs use different bytecode for the different kinds of things pushed (`CONSTI` for a constant-integer vs `CONSTL` for constant-long vs `CONSTS` for constant-string, for example), while others use a "constant pool" to hold all of the constants in use by this program, and `CONST 5` means "push the constant found in constantPool[5] onto the stack".

### Add other numeric types
Many platforms differentiate between 8-, 16-, 32-, 64-, and 128-bit values. (Some go even larger.) Without changing the fundamental structure of the VirtualMachine as it exists now, how would you add support for those types?

### Add some type-safety
What happens if we try to add an integer value to a string? What happens when we try to add an integer value to a floating-point value? What should happen? More importantly, where and how do we track the type information of a given piece of data, so that we know what it is we're adding (or subtracting or dividing or ...)?

### Create an assembly text format
Right now all the bytecode we execute is stored as a part of the tests we're writing; a more reasonable virtual machine would have the ability to execute files that contain our bytecode. What sort of file format would offer forward-compatibility with new features we might add to the VM, while still being able to execute "v1" bytecode scripts we might write today? Write an "assembler" that takes a text-based format and "assemble" it into the raw array of bytes that we've been working with; when you're done with that, write a "disassembler" that does the opposite. How much code can you reuse between these two utilities? Make sure you can "round-trip" between them: assemble a program into binary, then disassemble the binary back into a text format that can be assembled into a binary again, all without losing anything along the way.
