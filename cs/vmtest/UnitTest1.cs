namespace vmtest;

using vm;

[TestClass]
public class UnitTest1
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
}