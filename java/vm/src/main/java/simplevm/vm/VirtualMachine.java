package simplevm.vm;

import java.util.Arrays;

public class VirtualMachine {
    int IP = 0;
    boolean trace = false;

    private void trace(String message) {
        if (trace) {
            System.out.println("TRACE: " + message);
        }
    }

    public void execute(Bytecode[] code) {
        for (IP = 0; IP < code.length; )
        {
            switch (code[IP])
            {
                case NOP:
                    // Do nothing!
                    trace("NOP");
                    break;
                case DUMP:
                    trace("DUMP");
                    System.out.println("IP: " + IP);
                    System.out.println("code: " + Arrays.toString(code));
                    break;
                case TRACE:
                    trace = !trace;
                    trace("TRACE");
                    break;
                default:
                    throw new RuntimeException("Unrecognized opcode: " + code[IP]);
            }
            IP++;
        }
    }
}
