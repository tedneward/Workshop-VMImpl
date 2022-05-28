namespace vm;

public enum Bytecode 
{
    NOP = 0
}

public class VirtualMachine
{
    int IP = 0;

    public void Execute(Bytecode[] code)
    {
        for (IP = 0; IP < code.Length; )
        {
            switch (code[IP])
            {
                case Bytecode.NOP:
                    // Do nothing!
                    break;
                default:
                    throw new Exception("Unrecognized opcode: " + code[IP]);
            }
            IP++;
        }
    }
}
