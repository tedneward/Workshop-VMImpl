package simplevm.vm;

public class Bytecode {
    private Bytecode() { 
        throw new VirtualMachine.Exception("Bytecode private ctor should never be called"); 
    }

    public static final int NOP = 0;
    public static final int DUMP = 1;
    public static final int TRACE = 2;
    public static final int PRINT = 3;
    public static final int FATAL = 4;

    // Stack manipulation
    public static final int CONST = 10;
    public static final int POP = 11;

    // Maths
    public static final int ADD = 20;
    public static final int SUB = 21;
    public static final int MUL = 22;
    public static final int DIV = 23;
    public static final int MOD = 24;
    public static final int ABS = 25;
    public static final int NEG = 26;
}
