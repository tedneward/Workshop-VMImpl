# Workshop-VMImpl: Step 4 (Globals)
Welcome to step 4! In this step, you'll implement a rough form of "static storage", which we normally call by a less delightful name: global variables (or global storage). We do this because there's a fair number of things that are appropriate to store in globals, and besides, it'll help us figure out how to do more interesting (and complicated) things later.

## Steps
Implementing globals will require two basic parts: providing the storage itself to which values can be read and written, and implementing the bytecode instructions that know how to store something to a global cell, and how to load a value from a global cell.

> Terminology note: We choose the terms "store" and "load" because "read" and "write" are often entirely unhelpful--are we reading from the storage, or are we reading from the stack? "Store" and "load" are generally more common in virtual machine literature for this reasonm as well.

### Provide the global storage
For our simple virtual machine, given that we only work with integer values, it's entirely appropriate to allocate another "chunk" of integers to use as our addressed global "memory". In essence, we'll treat this array as if it were addressable memory in the virtual machine's working memory space.

Towards that end, create a new integer array field/property in the VirtualMachine, allocate a decent chunk of integers (I use 32--we don't want too many of them!), and call it "globals".

You may want to update your "trace" and "dump" functions to display the full contents of memory as well, so that it's easier to diagnose what's happening inside the virtual machine as you go.

We will also want to be able to manually manipulate the globals' contents from our tests, so either make the "globals" public, or create methods to access and manipulate their contents ("storeGlobal" and "loadGlobal", for example). (In my implementation, I just make "globals" accessible to the test code).

### Provide the bytecode instructions
Now we introduce two bytecode instructions: `GSTORE`, to put the top of the stack into a addressed global cell, and `GLOAD`, to take a copy of the value from an addressed global cell and push it onto the top of the stack.

* Implement `GSTORE`. It should take one parameter in the bytecode stream--the address in the globals array to which to store the value--and it should consume one operand off the top of the bytecode stack (the value to store). So, `CONST 15`/`GSTORE 0` should pop the 15 on the top of the stack, and store it to the first cell in "globals" ("globals[0]").

* Implement `GLOAD`. It should take one parameter in the bytecode stream--the address in the globals array to which to store the value--and it should push that value onto the top of the stack. So, `CONST 15`/`GSTORE 0`/`GLOAD 0` should (after storing 15 into globals[0]), read the value from globals[0] and push it onto the stack.

