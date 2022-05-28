namespace vmtest;

using vm;

[TestClass]
public class SimpleTests
{
    [TestMethod]
    public void TestTest()
    {
        Assert.AreEqual(2, 1 + 1);
        //Assert.AreEqual(2, 1 - 1); // just to make sure tests can fail, just in case
    }

    [TestMethod]
    public void TestInstantiation()
    {
        VirtualMachine vm = new VirtualMachine();

        Assert.IsTrue(vm != null);
    }

    [TestMethod]
    public void TestNOP()
    {
        VirtualMachine vm = new VirtualMachine();

        Bytecode[] code = {
            Bytecode.NOP
        };
        vm.Execute(code);

        // If we get here, we're good
        Assert.IsTrue(vm != null);
    }

    [TestMethod]
    public void TestNOPs()
    {
        VirtualMachine vm = new VirtualMachine();

        Bytecode[] code = {
            Bytecode.NOP,
            Bytecode.NOP,
            Bytecode.NOP,
            Bytecode.NOP
        };
        vm.Execute(code);

        // If we get here, we're good
        Assert.IsTrue(vm != null);
    }

    [TestMethod]
    public void TestDUMP()
    {
        VirtualMachine vm = new VirtualMachine();

        Bytecode[] code = {
            Bytecode.NOP,
            Bytecode.DUMP
        };
        vm.Execute(code);

        // If we get here, we're good
        Assert.IsTrue(vm != null);
    }
    [TestMethod]
    public void TestTRACE()
    {
        VirtualMachine vm = new VirtualMachine();

        Bytecode[] code = {
            Bytecode.TRACE,
            Bytecode.NOP,
            Bytecode.DUMP
        };
        vm.Execute(code);

        // If we get here, we're good
        Assert.IsTrue(vm != null);
    }
}
