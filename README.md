# Workshop-VMImpl: Step 1 (Mathematics) - Completed!
Welcome to my implementation of step 1! This will essentially be the same code as what's in the branch `step2begin`, but this document will be different (since the `step2begin` branch will contain the instructions for Step 2).

The code in this step is from my implementation of the `step1end` branch; you are not obligated to use it, so long as your tests passed at the end of step 1.

## Important Note: Tests
Note that both projects have unit tests in place already ***that will fail***, out of the box, right now. These are intended as very rough guides to make sure that your implementation meets our "expectations" (basically, that your code will work for future steps in the manner in which the workshop creator is expecting!). These are not considered to be extensive or comprehensive or even good examples of tests or TDD--they're just there to help make sure we're all on the same path together, and to give you a sense of what we're trying to build (in those situations where the text above isn't clear enough).

You are, of course, encouraged to add a few of your own, just to make sure that the code coverage number is the industry-standard 110%!

## Steps
We will now add a few maths opcodes. These are generally characterized into two camps: the binary operators (add, subtract, multiply, divide, modulo, and so on), which take two parameters, and the unary operators (absolute-value, and negation), which take one parameter. All will also have the characteristic that they will consume their parameters off the stack, but produce a result back onto the top of the stack.

### Unary operators
These take one parameter off the stack, and push their result back onto the stack.

* Implement the `ABS` bytecode, which calculates the absolute value of the value at the top of the stack. That is to say, unlike `CONST`, which expected its parameter to be present in the bytecode, `ABS` (and the other mathematical operators) pops its operand off the stack, does its calculation, and then pushes its result back onto the stack. Thus, `CONST -10`/`ABS` will result in `10` at the top of the stack.

* Implement the `NEG` bytecode, which provides the mathematical "negation" operation: it takes a positive value and converts it to negative, or a negative value back into positive. Thus, `CONST 10`/`NEG` will result in `-10` at the top of the stack, and `CONST 10`/`NEG`/`NEG` will result in `10` (10 -> -10 -> 10) at the top of the stack.

### Binary operators
These take the top two parameters off the stack, and push their result back onto the stack.

* Implement the `ADD` bytecode, which sums up the top two parameters off the stack, and pushes their result back onto the stack.

* Implement `SUB`.

* Implement `MUL`.

* Implement `DIV`.

* Implement `MOD`, the modulo operator. (For those who aren't familiar with this operation, modulo is the "remainder" operation from division; 10 / 2 = 5 with no remainder, so 10 modulo 2 is 0. Similarly 9 / 4 is 2 with a remainder of 1, so 9 modulo 4 is 1.)

> Discussion opportunity: The unary and binary operators are, in many respects, very similar to one another. What sort of refactoring opportunities do you see here, in general and/or in your implementation? Take a second to add a few tests to keep yourself honest, then do some refactoring.
