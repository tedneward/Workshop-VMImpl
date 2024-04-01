namespace vmtest;

using vm;

[TestClass]
public class StackTests
{
    [TestMethod]
    public void TestPush()
    {
        VirtualMachine vm = new VirtualMachine();

        vm.Push(27);

        Assert.AreEqual(1, vm.Stack.Length);
        Assert.AreEqual(27, vm.Stack[0]);
    }
    [TestMethod]
    public void TestPushPop()
    {
        VirtualMachine vm = new VirtualMachine();

        vm.Push(27);
        Assert.AreEqual(1, vm.Stack.Length);

        int value = vm.Pop();

        Assert.AreEqual(27, value);
        Assert.AreEqual(0, vm.Stack.Length);
    }
    [TestMethod]
    public void TestCONST()
    {
        VirtualMachine vm = new VirtualMachine();

        vm.Execute(Bytecode.CONST, 34);
        vm.Execute(new Bytecode[] {
            Bytecode.CONST, (Bytecode)27,
        });

        Assert.AreEqual(2, vm.Stack.Length);
        Assert.AreEqual(34, vm.Stack[0]);
        Assert.AreEqual(27, vm.Stack[1]);
    }
    [TestMethod]
    public void TestCONSTPOP()
    {
        VirtualMachine vm = new VirtualMachine();

        vm.Execute(new Bytecode[] {
            Bytecode.CONST, (Bytecode)27,
            Bytecode.POP,
        });

        Assert.AreEqual(0, vm.Stack.Length);
    }
}
