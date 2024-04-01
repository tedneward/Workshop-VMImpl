# Workshop-VMImpl: Step 2 (Comparisons) - Complete!
Welcome to my implementation of step 2! 

## Implementation notes

### Long-handed bytecode implementations
I choose to implement this the "long way", in that I essentially duplicate the code blocks for EQ, NE, GT, GTE, LT and LTE, with many of them different only in a single character or two ("==" vs "!=" vs "<" vs "<=" and so on ....). Frankly, this is a nod to the realization that there aren't many more of these we're going to add in this particular set, and any implementation that makes it easier to condense the number of lines of code would introduce a slight performance penalty. Although performance is NOT a goal for this workshop, it's important to realize that in a situation like this--a tight loop executing as fast as it can--things we'd normally do to make the code more readable or extensible may not always be the most appropriate. (In this particular case, I think it's plenty readable, and there's little to no chance that we'll want to fix or change the behavior of these instructions, so I consider the DRY rule to be unnecessary here. YMMV.)

### "Right-first rule"
As with the mathematical ops, I choose to follow a "right-first" rule, wherein the right-hand argument (the "y" in "x op y") is retrieved first, then the left.
