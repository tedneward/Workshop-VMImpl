# Workshop-VMImpl: Step 1 (Mathematics) - Completed!
Welcome to my implementation of step 1!

## Implementation Notes

### Long-handed bytecode implementations
I choose to implement this the "long way", in that I essentially duplicate the code blocks for ADD, SUB, MUL, DIV, and MOD, with many of them different only in a single character or two ("+" vs "-" vs "*" vs "/" and so on ....). Frankly, this is a nod to the realization that there aren't many more of these we're going to add in this particular set, and any implementation that makes it easier to condense the number of lines of code would introduce a slight performance penalty. Although performance is NOT a goal for this workshop, it's important to realize that in a situation like this--a tight loop executing as fast as it can--things we'd normally do to make the code more readable or extensible may not always be the most appropriate. (In this particular case, I think it's plenty readable, and there's little to no chance that we'll want to fix or change the behavior of these instructions, so I consider the DRY rule to be unnecessary here. YMMV.)

### "Right-first rule"
Note that if we want the author of the bytecode to be able to see things in a "left to right" order of pushing opcodes onto the stack, then we have to read them in *reverse* order, popping the right-hand operand first from the stack, then the left. Different virtual machines (and different languges, when they generate the assembly for native CPU instructions) have different opinions of this, and the decisions they make are referred to as "calling conventions". 

The C programming language has some very specific rules about this, leading to the near-universal "C calling convention" that is in place for almost every operating system ever written since the 1970s. This, in turn, means that any virtual machine that wants to be able to call out to C code (or something that follows the rules for a C function, anyway) must understand the C calling convention, and push arguments and such on the execution stack exactly the way C expects them to be.
