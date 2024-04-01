namespace vmtest;

using vm;

[TestClass]
public class MathTests
{
    [TestMethod]
    public void TestADD()
    {
        VirtualMachine vm = new VirtualMachine();

        vm.Execute(new Bytecode[] {
            Bytecode.CONST, (Bytecode)5,
            Bytecode.CONST, (Bytecode)5,
            Bytecode.ADD,
        });

        Assert.AreEqual(1, vm.Stack.Length);
        Assert.AreEqual(10, vm.Stack[0]);
    }
    [TestMethod]
    public void TestSUB()
    {
        VirtualMachine vm = new VirtualMachine();
        vm.Execute(new Bytecode[] {
            Bytecode.CONST, (Bytecode)15,
            Bytecode.CONST, (Bytecode)5,
            Bytecode.SUB,
        });

        Assert.AreEqual(1, vm.Stack.Length);
        Assert.AreEqual(10, vm.Stack[0]);
    }
    [TestMethod]
    public void TestMUL()
    {
        VirtualMachine vm = new VirtualMachine();
        vm.Execute(new Bytecode[] {
            Bytecode.CONST, (Bytecode)5,
            Bytecode.CONST, (Bytecode)2,
            Bytecode.MUL,
        });

        Assert.AreEqual(1, vm.Stack.Length);
        Assert.AreEqual(10, vm.Stack[0]);
    }
    [TestMethod]
    public void TestDIV()
    {
        VirtualMachine vm = new VirtualMachine();
        vm.Execute(new Bytecode[] {
            Bytecode.CONST, (Bytecode)20,
            Bytecode.CONST, (Bytecode)2,
            Bytecode.DIV,
        });

        Assert.AreEqual(1, vm.Stack.Length);
        Assert.AreEqual(10, vm.Stack[0]);
    }
    [TestMethod]
    public void TestMOD()
    {
        VirtualMachine vm = new VirtualMachine();
        vm.Execute(new Bytecode[] {
            Bytecode.CONST, (Bytecode)30,
            Bytecode.CONST, (Bytecode)20,
            Bytecode.MOD,
        });

        Assert.AreEqual(1, vm.Stack.Length);
        Assert.AreEqual(10, vm.Stack[0]);
    }
    [TestMethod]
    public void TestABS()
    {
        VirtualMachine vm = new VirtualMachine();
        vm.Execute(new Bytecode[] {
            Bytecode.CONST, (Bytecode)30,
            Bytecode.ABS,
        });

        Assert.AreEqual(1, vm.Stack.Length);
        Assert.AreEqual(30, vm.Stack[0]);
    }
    [TestMethod]
    public void TestNEG()
    {
        VirtualMachine vm = new VirtualMachine();
        vm.Execute(new Bytecode[] {
            Bytecode.CONST, (Bytecode)(-10),
            Bytecode.NEG,
        });

        Assert.AreEqual(1, vm.Stack.Length);
        Assert.AreEqual(10, vm.Stack[0]);
    }
    [TestMethod]
    public void TestNEGNEG()
    {
        VirtualMachine vm = new VirtualMachine();
        vm.Execute(new Bytecode[] {
            Bytecode.CONST, (Bytecode)(10),
            Bytecode.NEG,
            Bytecode.NEG,
        });

        Assert.AreEqual(1, vm.Stack.Length);
        Assert.AreEqual(10, vm.Stack[0]);
    }
}
