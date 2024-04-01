namespace vm;

public enum Bytecode 
{
    NOP,
    DUMP,
    TRACE,
    PRINT,
    FATAL,

    // Stack opcodes
    CONST,
    POP,

    // Math opcodes (binary)
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,

    // Math opcodes (unary)
    ABS,
    NEG,

    // Comparison
    EQ,
    NEQ,
    GT,
    LT,
    GTE,
    LTE,
}


public class VirtualMachine
{
    // Tracing
    //
    bool trace = false;
    private void Trace(string message)
    {
        if (trace)
            Console.WriteLine("TRACE: {0}", message);
    }

    // Diagnostics
    //
    private void Dump()
    {
        Console.WriteLine("SimpleVM - DUMP");
        Console.WriteLine("===============");
        Console.WriteLine("IP: {0} / Trace: {1}", IP, trace);
        Console.WriteLine("Working stack (SP {0}): {1}", SP, String.Join(", ", Stack));
    }

    // Stack management
    //
    int SP = -1; // points to the current top of stack
    int[] stack = new int[100];
    public int[] Stack { get { return stack.Take(SP+1).ToArray(); } }
    public void Push(int operand)
    {
        Trace("Push: " + operand);
        stack[++SP] = operand;
        Trace(" -->  Stack: " + String.Join(",", stack));
    }
    public int Pop()
    {
        Trace("Pop");
        int result = stack[SP--];
        Trace(" -->  Stack: " + String.Join(",", stack));
        return result;
    }



    public void Execute(Bytecode opcode, params int[] operands)
    {
        switch (opcode)
        {
            case Bytecode.NOP:
                // Do nothing!
                Trace("NOP");
                break;
            case Bytecode.DUMP:
                Trace("DUMP");
                Dump();
                break;
            case Bytecode.TRACE:
                trace = !trace;
                Trace("TRACE " + trace);
                break;
            case Bytecode.PRINT:
                Trace("PRINT");
                Console.WriteLine(Pop());
                break;
            case Bytecode.FATAL:
                Trace("FATAL");
                throw new Exception(String.Format("FATAL exception thrown; IP {0}",IP));
            case Bytecode.CONST:
                int operand = operands[0];
                Trace("CONST " + operand);
                Push(operand);
                break;
            case Bytecode.POP:
                Trace("POP");
                // throw away returned value
                Pop();
                break;

            // Mathematical ops
            case Bytecode.ADD:
            {
                Trace("ADD");
                int rhs = Pop();
                int lhs = Pop();
                Push(lhs + rhs);
                break;
            }
            case Bytecode.SUB:
            {
                Trace("SUB");
                int rhs = Pop();
                int lhs = Pop();
                Push(lhs - rhs);
                break;
            }
            case Bytecode.MUL:
            {
                Trace("MUL");
                int rhs = Pop();
                int lhs = Pop();
                Push(lhs * rhs);
                break;
            }
            case Bytecode.DIV:
            {
                Trace("DIV");
                int rhs = Pop();
                int lhs = Pop();
                Push(lhs / rhs);
                break;
            }
            case Bytecode.MOD:
            {
                Trace("MOD");
                int rhs = Pop();
                int lhs = Pop();
                Push(lhs % rhs);
                break;
            }
            case Bytecode.ABS:
            {
                Trace("ABS");
                int val = Pop();
                Push(Math.Abs(val));
                break;
            }
            case Bytecode.NEG:
            {
                Trace("NEG");
                int val = Pop();
                Push(-val);
                break;
            }
            
            // Comparison ops
            case Bytecode.EQ:
            {
                Trace("EQ");
                int rhs = Pop();
                int lhs = Pop();
                Push(lhs == rhs ? 1 : 0);
                break;
            }
            case Bytecode.NEQ:
            {
                Trace("NEQ");
                int rhs = Pop();
                int lhs = Pop();
                Push(lhs != rhs ? 1 : 0);
                break;
            }
            case Bytecode.GT:
            {
                Trace("GT");
                int rhs = Pop();
                int lhs = Pop();
                Push(lhs > rhs ? 1 : 0);
                break;
            }
            case Bytecode.LT:
            {
                Trace("LT");
                int rhs = Pop();
                int lhs = Pop();
                Push(lhs < rhs ? 1 : 0);
                break;
            }
            case Bytecode.GTE:
            {
                Trace("GTE");
                int rhs = Pop();
                int lhs = Pop();
                Push(lhs >= rhs ? 1 : 0);
                break;
            }
            case Bytecode.LTE:
            {
                Trace("LTE");
                int rhs = Pop();
                int lhs = Pop();
                Push(lhs <= rhs ? 1 : 0);
                break;
            }
        }
    }
    int IP = -1;
    public void Execute(Bytecode[] code)
    {
        for (IP = 0; IP < code.Length; )
        {
            Bytecode opcode = code[IP];
            switch (opcode)
            {
                // 0-operand opcodes
                case Bytecode.NOP:
                case Bytecode.DUMP:
                case Bytecode.TRACE:
                case Bytecode.PRINT:
                case Bytecode.FATAL:
                case Bytecode.POP:
                case Bytecode.ADD:
                case Bytecode.SUB:
                case Bytecode.MUL:
                case Bytecode.DIV:
                case Bytecode.MOD:
                case Bytecode.ABS:
                case Bytecode.NEG:
                case Bytecode.EQ:
                case Bytecode.NEQ:
                case Bytecode.GT:
                case Bytecode.LT:
                case Bytecode.GTE:
                case Bytecode.LTE:
                    Execute(opcode);
                    IP += 1;
                    break;

                // 1-operand opcodes
                case Bytecode.CONST:
                    int operand = (int)code[IP + 1];
                    Execute(opcode, operand);
                    IP += 2;
                    break;

                // 2-operand opcodes

                // Unrecognized opcode
                default:
                    throw new Exception("Unrecognized opcode: " + code[IP]);
            }
        }
    }
}
