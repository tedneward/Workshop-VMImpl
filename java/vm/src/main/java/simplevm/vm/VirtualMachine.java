package simplevm.vm;

public class VirtualMachine {
    int IP = 0;

    public void execute(Bytecode[] code) {
        for (IP = 0; IP < code.length; )
        {
            switch (code[IP])
            {
                case NOP:
                    // Do nothing!
                    break;
                default:
                    throw new RuntimeException("Unrecognized opcode: " + code[IP]);
            }
            IP++;
        }
    }
}
