namespace vm;

public enum Bytecode 
{
    NOP,
    DUMP,
    TRACE
}

public class VirtualMachine
{
    int IP = 0;
    bool trace = false;

    public void Execute(Bytecode[] code)
    {
        for (IP = 0; IP < code.Length; )
        {
            switch (code[IP])
            {
                case Bytecode.NOP:
                    // Do nothing!
                    break;
                case Bytecode.DUMP:
                    Console.WriteLine("IP: {0}", IP);
                    Console.WriteLine("code: [{0}]", String.Join(",", code));
                    break;
                case Bytecode.TRACE:
                    trace = !trace;
                    break;
                default:
                    throw new Exception("Unrecognized opcode: " + code[IP]);
            }
            IP++;
        }
    }
}
