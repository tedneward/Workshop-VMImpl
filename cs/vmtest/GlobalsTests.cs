namespace vmtest;

using vm;

[TestClass]
public class GlobalsTests
{
    [TestMethod]
    public void TestGlobalLoad()
    {
        VirtualMachine vm = new VirtualMachine();
        vm.Globals[0] = 27;
        vm.Execute(new Bytecode[] {
            Bytecode.GLOAD, (Bytecode)0
        });

        Assert.AreEqual(1, vm.Stack.Length);
        Assert.AreEqual(27, vm.Stack[0]);
    }
    [TestMethod]
    public void TestGlobalStore()
    {
        VirtualMachine vm = new VirtualMachine();
        vm.Execute(new Bytecode[] {
            Bytecode.CONST, (Bytecode)27,
            Bytecode.GSTORE, (Bytecode)0
        });

        Assert.AreEqual(0, vm.Stack.Length);
        Assert.AreEqual(27, vm.Globals[0]);
    }

    [TestMethod]
    public void TestGlobals()
    {
        VirtualMachine vm = new VirtualMachine();
        vm.Execute(new Bytecode[] {
            Bytecode.CONST, (Bytecode)27,
            Bytecode.GSTORE, (Bytecode)0,
            Bytecode.GLOAD, (Bytecode)0,
            Bytecode.GLOAD, (Bytecode)0,
            Bytecode.ADD,
            Bytecode.GSTORE, (Bytecode)1
        });

        // Stack should be empty
        Assert.AreEqual(0, vm.Stack.Length);

        // Global 0 should have our CONST 27 in it
        Assert.AreEqual(27, vm.Globals[0]);
        // Global 1 should have 27 + 27
        Assert.AreEqual(27 + 27, vm.Globals[1]);
    }

}
