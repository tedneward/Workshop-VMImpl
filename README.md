# Workshop-VMImpl: Step 0 (Infrastructure) - Completed!
Welcome to my implementation of step 0! 

The code seen here will be the same code as what's in the branch `step1begin`, but this document will be different (since the `step1begin` branch will contain the instructions for Step 1).

## Implementation Notes
In the README's for each of the "end" branches, I'll include notes for what is in my implementation; you may find them interesting, you may not. :-)

### Stack
I choose my stack to start from 0 and increment the SP index as more things get pushed onto the stack. Note that for simplicity in the code, I initialize SP to be -1 to start, and remember to always increment SP in the push method before assigning the value to the current SP-indexed slot in the stack array. That way, it balances out when I retrieve the element from the array before decrementing SP. (Remember that prefix "++" means "increment before use" and postfix "--" means "decrement after use" in both Java and C#. In languages that don't support that precise semantic, I'd need to be a little more verbose in the implementation.)

It took me quite a few iterations (and it was what really incentivized me to put unit tests around all this!) to get this logic exactly right.

### Tracing
I choose to trace out every single bytecode that gets executed, which would be a pretty significant performance hit in a production-level VM. This is not a production-level VM.

### Incrementing IP
In both the C# and Java version, I choose to create a "for" loop that doesn't have a step expression to it, as I'm going to increment `ip` directly. In the Java case, I do it right next to where we `execute` the bytecode, whereas in the C# version I do it at the bottom of the loop. The C# version is more tempting, but it'll run into issues with jumping instructions later, since I will want to *not* touch the IP at the bottom of the loop then.

Truthfully, my first bytecode VM had the `IP++` at the end of the loop (the C# version), and it became a source of bugs when I introduced jumps. I leave it here in the C# version mostly so that people can see (and maybe feel) the implications of doing it this way.
