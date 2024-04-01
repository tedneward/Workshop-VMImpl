namespace vmtest;

using vm;

[TestClass]
public class JumpTests
{
    [TestMethod]
    public void TestJMP()
    {
        VirtualMachine vm = new VirtualMachine();

        // CONST and FATALs here should be bypassed...
        vm.Execute(new Bytecode[] {
            /* 0*/ Bytecode.JMP, (Bytecode)6,
            /* 2*/ Bytecode.CONST, (Bytecode)12,
            /* 4*/ Bytecode.FATAL,
            /* 5*/ Bytecode.FATAL,
            /* 6*/ Bytecode.NOP
        });

        // ... leaving nothing on the stack
        Assert.AreEqual(0, vm.Stack.Length);
    }
    
    [TestMethod]
    public void TestRJMP()
    {
        VirtualMachine vm = new VirtualMachine();

        // CONST and FATALs here should be bypassed...
        vm.Execute(new Bytecode[] {
            /* 0*/ Bytecode.RJMP, (Bytecode)6,  // JMP to current IP (0) + 6 ==> 6
            /* 2*/ Bytecode.CONST, (Bytecode)12,
            /* 4*/ Bytecode.FATAL,
            /* 5*/ Bytecode.FATAL,
            /* 6*/ Bytecode.NOP
        });

        // ... leaving nothing on the stack
        Assert.AreEqual(0, vm.Stack.Length);
    }

    [TestMethod]
    public void TestJMPI()
    {
        VirtualMachine vm = new VirtualMachine();

        // CONSTs here should be bypassed...
        vm.Execute(new Bytecode[] {
            /* 0*/ Bytecode.CONST, (Bytecode)7,
            /* 2*/ Bytecode.JMPI,
            /* 3*/ Bytecode.CONST, (Bytecode)12,
            /* 5*/ Bytecode.CONST, (Bytecode)27,
            /* 7*/ Bytecode.NOP
        });

        // ... leaving nothing on the stack
        Assert.AreEqual(0, vm.Stack.Length);
    }

    [TestMethod]
    public void TestRJMPI()
    {
        VirtualMachine vm = new VirtualMachine();

        // CONST and FATALs here should be bypassed...
        vm.Execute(new Bytecode[] {
            /* 0*/ Bytecode.CONST, (Bytecode)5,
            /* 2*/ Bytecode.RJMPI, // Jump to current IP (2) + 5 => 7
            /* 3*/ Bytecode.CONST, (Bytecode)12,
            /* 5*/ Bytecode.FATAL,
            /* 6*/ Bytecode.FATAL,
            /* 7*/ Bytecode.NOP
        });

        // ... leaving nothing on the stack
        Assert.AreEqual(0, vm.Stack.Length);
    }

    [TestMethod]
    public void TestLotsofJumps() {
        VirtualMachine vm = new VirtualMachine();
        vm.Execute(new Bytecode[] {
            /* 0*/ Bytecode.TRACE,
            /* 1*/ Bytecode.JMP, (Bytecode)4,  // bypass FATAL opcode
            /* 3*/ Bytecode.FATAL,
            /* 4*/ Bytecode.JMP, (Bytecode)7,
            /* 6*/ Bytecode.FATAL,
            /* 7*/ Bytecode.JMP, (Bytecode)10,
            /* 9*/ Bytecode.FATAL,
            /*10*/ Bytecode.NOP
        });

        Assert.AreEqual(0, vm.Stack.Length);
    }
}
