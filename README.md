# Workshop-VMImpl: Step 2 (Comparisons)
Welcome to step 2! In this step, we will implement the various comparison operators, which are actually very, very similar to the mathematics operators you just finished. (In fact, I debated whether or not to put both steps into a single one.)

The code in this step is from my implementation of the `step1end` branch; you are not obligated to use it, so long as your tests passed at the end of step 1.

## Important Note: Tests
Note that both projects have unit tests in place already ***that will fail***, out of the box, right now. These are intended as very rough guides to make sure that your implementation meets our "expectations" (basically, that your code will work for future steps in the manner in which the workshop creator is expecting!). These are not considered to be extensive or comprehensive or even good examples of tests or TDD--they're just there to help make sure we're all on the same path together, and to give you a sense of what we're trying to build (in those situations where the text above isn't clear enough).

You are, of course, encouraged to add a few of your own, just to make sure that the code coverage number is the industry-standard 110%!

## Steps
We will now add the range of comparison opcodes (equals, not-equals, greater-than, greater-than-or-equals, and so on). These are all binary operators, taking two elements off the top of the stack, performing their comparison, and pushing the result (a "1" for true, a "0" for false) onto the top of the stack.

> Implementation note: Although the "1" for true and "0" for false is a pretty universal assumption, some languages and platforms have experimented with other values here--pity the poor Visual Basic programmer (pre-.NET version), where "0" was true, and "-1" wsa false. To this day, I've never heard any of VB language designers explain why they went with that.

Note that for some operators (equals, not-equals) the order of parameters on the stack is not important, but for others (greater-than, lesser-than, etc) it will be important for you to make sure you are clear as to which of the two parameters on the stack are the "left" of the operation, and which is the "right" (as you no doubt discovered when implementing `SUB`, `DIV`, and `MOD` in the last step.)

### Equality (==, !=) operators
These take two parameters off the stack, and push their result back onto the stack.

* Implement the `EQ` bytecode, which takes two parameters off the stack, compares their numerical values (since they are all integers), and pushes either a "1" if they are the same value, or a "0" if they are not, onto the top of the stack.
* Implement the `NEQ` bytecode, which does the inverse of the `EQ` bytecode.

### Relative (<, >, <=, or >=) operators
These take the top two parameters off the stack, and push their result back onto the stack.

* Implement `GT`, which is our "greater-than" bytecode.
* Implement `GTE`, which is our "greather-than-or-equal" bytecode.
* Implement `LT`, which is our "lesser-than" bytecode.
* Implement `LTE`, which is our "lesser-than-or-equal" bytecode.

> Discussion opportunity: All of these operators have the interesting property in that they are all deeply similar to one another--`GT` is essentially the inverse of `LTE`, for example. What's the absolute minimum operator set you could use here? (My intuition suggests three out of the six, but I'm no mathematician.)

