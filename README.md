# Workshop-VMImpl: Step 3 (Branching)
Welcome to step 3! In this step, we implement some bytecode instructions to jump and branch, all of which have the practical effect of changing the instruction pointer (IP) for the next instruction to execute.

## Important Note: Tests
Note that both projects have unit tests in place already ***that will fail***, out of the box, right now. These are intended as very rough guides to make sure that your implementation meets our "expectations" (basically, that your code will work for future steps in the manner in which the workshop creator is expecting!). These are not considered to be extensive or comprehensive or even good examples of tests or TDD--they're just there to help make sure we're all on the same path together, and to give you a sense of what we're trying to build (in those situations where the text above isn't clear enough).

You are, of course, encouraged to add a few of your own, just to make sure that the code coverage number is the industry-standard 110%!

## Steps
There's several different kinds of jumping/branching instructions we can consider, all of which are useful in different scenarios. 

### Absolute direct jump
The first, the `JMP` bytecode instruction, unconditionally sets the new instruction pointer to be the value passed as a parameter in the bytecode. So, for example, if the bytecode stream contains `JMP 12`, the next instruction to be executed is the 12th instruction in the stream, regardless of what that is.

> Implementation note: Many CPU assembly languages support this same kind of instruction, and it became the height of hacker culture back in the day to implement a working program that could jump right into the *middle* of an instruction--that is, to jump to the location specifying not an instruction, but an operand, which was interpreted as an instruction, which actually worked without error. (It was a simpler time....)

### Relative direct jump
The second, the `RJMP`, or "relative jump", bytecode instruction, unconditionally sets the instruction pointer to be the current instruction pointer, adjusted by the value passed as a parameter. So an `RJMP 3` says to jump to 3 instructions ahead of the current instruction, and an `RJMP -3` says to jump *backwards* by three instructions.

### Absolute indirect jump
The third, the `JMPI`, or "indirect jump", bytecode instruction, takes its absolute target location from the top of the operation stack (rather than from the bytecode stream), and sets the instruction pointer to that value. So a bytecode stream of `CONST 5`/`JMPI` would jump to IP 5 and begin executing from there.

> Implementation note: In many languages, this is actually handled well beneath the surface of the VM through "dynamic dispatch" calls to virtual methods. In many of the object languages, for example, an object has a "v-table" (or virtual-table-of-function-pointers), and when executing a method on an object, the instruction stream loads the address of the appropriate method from the v-table, then calls to the location specified by that pointer. It's kinda trippy when you first see it.

### Relative indirect jump
The third, the `RJMPI`, or "relative indirect jump", bytecode instruction, takes its relative target location from the top of the operation stack (rather than from the bytecode stream), and sets the instruction pointer to that value. So a bytecode stream of `CONST -5`/`RJMPI` would jump to IP (current IP -5) and begin executing from there.

## Note
There is another form of jump/branch, often a "call" or "go-sub" instruction, in which the virtual machine "remembers" the instruction pointer at which the call takes place, and expects a later "return" instruction to cause the VM to come back to the original location (in order to execute the next instruction). This is usually in conjunction with more in the way of "procedure" support, which we'll explore in Step 6.

