# Workshop-VMImpl: Step 4 (Globals) - Completed!
Welcome to my implementation of step 4! 

## Implementation notes

### Globals initialization
I don't explicitly initialize the contents of "globals" to zero once the array is allocated, so technically there's a chance that there's values already in there other than 0, but both the JVM and CLR explicitly state that array contents are initialized to 0 as part of allocation, so this shouldn't be a problem.

### Dump/Trace
I dump the state of global storage as part of the "dump" method, and rather than check which cells are occupied/used and which aren't, I just dump the whole set (which I think is more accurate, anyway).

### GSTORE and GLOAD
Keep in mind that each of these are going to take one parameter from the bytecode (the "address" of the global to affect) as well as interacting with the operand stack (either pushing or popping a value). Make sure to keep straight in your own mind which is which!

