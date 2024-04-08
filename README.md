# Workshop-VMImpl: Step 5 (Procedures and Locals)
Welcome to step 5! In this step, you'll take a major step, implementing functionality to provide procedure calls--the ability to define a procedure, call it with parameters, and return back to (just after) the point of call without having to manage the stack explicitly. Because each procedure call can/should support local variable declarations, we'll also support local storage, similar to how we did global storage, but scoped to the local call frame.

## Steps
Procedure calls, from an assembly language perspective, are essentially a formalized convention around three things:

* the location of parameters to the procedure call,
* the location of the return address, and
* a scheme by which local variables can be declared and reclaimed at the termination of the procedure call

For this virtual machine, we will create a collection of "stack frames" (also known as "activation records", or by the more colloquial "call stack") that exist as a separate entity to the operations stack. While a more close-to-x86 representation would have us store procedure parameters and local variables on the stack, it's much (much) easier to have a separate data structure to store the call stack--generating stack traces, for example, is much easier when there's a formal list of each call, along with the locals allocated within that stack frame.

> NOTE: This approach is the exact same approach as used by the JVM and CLR. Remember, everything we do here is an abstraction, and when (if) our implementation reaches the point of doing JIT compilation to native CPU instructions, we would generation machine code to use the approach required by whatever the CPU's convention is.

In some virtual machines, by the way, procedures (or methods) are defined apart from the main bytecode stream, and the virtual machine switches between which bytecode stream it is executing. We will keep it simple, and assume that all the procedures are defined in one contiguous stream of bytecode. That means it will be left up to the programmer (you) to make sure that each procedure's start and end don't overlap with any other procedure's start and end (unless you really want them to for some strange reason). 

### Create CallFrame
The first thing we require is a `CallFrame` type (which we will drop into a linked list called "frames" and grow/shrink as calls are created). This `CallFrame` will contain only a few things:

* an int array called `locals`, which is where locals to the procedure will be allocated,
* an int called `returnAddress`, which will contain the IP location for where we wish to return when this procedure is finished
* a constructor to initialize locals to a fixed-size array of 32 integers. 

> NOTE: in some VMs, such as the JVM, the size of the locals storage space is determined at runtime by some metadata defined as part of the code being loaded--in the JVM, you can see this in javap-generated output as "locals: x". As it turns out, the JVM actually stores a great deal of information about locals in methods as part of its metadata, but only retains it if the "debug" flag is on during javac compilation. The CLR does something similarly in its method metadata tables.

Thus:

* create the `CallFrame` type

    > Java implementation NOTE: if you choose to define the `CallFrame` type inside of the `VirtualMachine` type in VirtualMachine.java, make sure it is declared as a "static" class, so that it doesn't drag along a pointer to the `VirtualMachine` in each and every instance of the `CallFrame`.

* create a field in the `VirtualMachine` called `frames` that is a linked list of `CallFrame`s
* create a method in the `VirtualMachine` called `fp` that will return the topmost `CallFrame`. ("fp" is our "frame pointer", which should always point to the currently-active call frame.)

### Implement CALL and RET
Now let's implement the `CALL` and `RET` bytecode, which will perform the procedure call and return-from-procedure, respectively. `CALL` will expect an address (integer offset into the code) as an operand. It will immediately create a new `CallFrame`, capture the return address (current IP plus 2), and add the `CallFrame` to `frames`, and continue execution from there. `RET`, on the other hand, will look at the current `CallFrame`, extract the `returnAddress`, set `ip` to point to that value, and then remove the current `CallFrame` from `frames` entirely.

### Implement STORE and LOAD
Finally, the `STORE` and `LOAD` instructions will store and load, like `GSTORE` and `GLOAD` do, but to locals in the current `CallFrame`, rather than to the global storage space. 

## Congratulations!
If you have completed this, and all the tests pass, you have completed the workshop!
