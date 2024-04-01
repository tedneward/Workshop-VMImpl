# Workshop-VMImpl: Step 3 (Branching) - Complete!
Welcome to my implementation of step 3!

## Some implementation notes

### All the jump instructions
In "execute" taking an array, I deliberately break out all the jump instructions into their own block (from the 0-parameter or 1-parameter blocks that've been there before), because we need to *not* adjust IP as part of fetching and executing the bytecode. It looks a little weird to me, personally, but it's the cleanest way I've found thus far to make it clear that the jumping instructions are not to touch IP once it's been adjusted.
