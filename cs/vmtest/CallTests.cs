namespace vmtest;

using vm;

[TestClass]
public class CallTests
{
    [TestMethod]
    public void TestSimpleCall()
    {
        VirtualMachine vm = new VirtualMachine();
        vm.Execute(new Bytecode[] {
            // 0: entrypoint
            /* 0*/ Bytecode.NOP,//TRACE,
            /* 1*/ Bytecode.CALL, (Bytecode)5,
            /* 3*/ Bytecode.JMP, (Bytecode)10,
            // 5: a simple print(12) function
            /* 5*/ Bytecode.CONST, (Bytecode)12,
            /* 6*/ Bytecode.PRINT,
            /* 7*/ Bytecode.RET,
            // 8: end
            /* 8*/ Bytecode.NOP,
            /* 9*/ Bytecode.NOP,
            /*10*/ Bytecode.NOP
        });
    }

    [TestMethod]
    public void TestCountdownFunction()
    {
        VirtualMachine vm = new VirtualMachine();
        vm.Execute(new Bytecode[] {
            // 0: entrypoint
            /*0*/ Bytecode.NOP,//TRACE,
            /*1*/ Bytecode.JMP, (Bytecode)25,
            // function countdown(count)
            //    expects count on top of stack; no return value
            /*3*/ Bytecode.STORE, (Bytecode)0,  // move count into locals[0]
            /*5*/ Bytecode.LOAD, (Bytecode)0,   // locals[0]
            /*7*/ Bytecode.PRINT,               // print
            /*8*/ Bytecode.LOAD, (Bytecode)0,   // locals[0]
            /*10*/Bytecode.CONST, (Bytecode)0,  // 0
            /*12*/Bytecode.EQ,                  // locals[0] == 0 ?
            /*13*/Bytecode.JNZ, (Bytecode)24,   // jump to return
            /*15*/Bytecode.LOAD, (Bytecode)0,   // locals[0] = locals[0] - 1
            /*17*/Bytecode.CONST, (Bytecode)1,
            /*19*/Bytecode.SUB,
            /*20*/Bytecode.STORE, (Bytecode)0,
            /*22*/Bytecode.JMP, (Bytecode)5,    // jump to top of loop
            /*24*/Bytecode.RET,
            // end
            /*25*/Bytecode.CONST, (Bytecode)5,  // countdown(5)
            /*27*/Bytecode.CALL, (Bytecode)3,   // CALL line 3
            /*29*/Bytecode.NOP
        });

        // ... leaving nothing on the stack
        Assert.AreEqual(0, vm.Stack.Length);
    }
}
