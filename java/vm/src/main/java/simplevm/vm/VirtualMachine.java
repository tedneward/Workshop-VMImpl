package simplevm.vm;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

import static simplevm.vm.Bytecode.*;

public class VirtualMachine {

    public static class Exception extends java.lang.RuntimeException {
        public Exception(String message) {
            super(message);
        }
    }

    // Tracing
    //
    boolean trace = false;
    private void trace(String message) {
        if (trace) {
            System.out.println("(IP " + ip + "):" + message);
        }
    }

    // Dump
    //
    private void dump() {
        System.out.println("SimpleVM DUMP");
        System.out.println("=============");
        System.out.println("IP: " + ip);
        System.out.println("Working stack (SP " + sp + "): " + Arrays.toString(Arrays.copyOfRange(stack, 0, sp+1)));
        System.out.println("Globals: " + Arrays.toString(globals));
    }

    // Stack management
    //
    int sp = -1;
    int[] stack = new int[100];
    int[] getStack() {
        if (sp > -1)
            return Arrays.copyOf(stack, sp+1);
        else
            return new int[] { };
    }
    public void push(int value) {
        stack[++sp] = value;
        trace("---> pushed " + value + "; stack: " + Arrays.toString(Arrays.copyOfRange(stack, 0, sp+1)));
    }
    public int pop() {
        int result = stack[sp--];
        trace("---> popped ; stack: " + Arrays.toString(Arrays.copyOfRange(stack, 0, sp+1)));
        return result;
    }

    // Globals
    //
    int[] globals = new int[32];
    int[] getGlobals() {
        return globals;
    }

    public void execute(int opcode, int... operands) {
        switch (opcode) {
            case NOP:
                // Do nothing!
                trace("NOP");
                break;
            case DUMP:
                trace("DUMP");
                dump();
                break;
            case TRACE:
                trace = !trace;
                trace("TRACE");
                break;
            case PRINT:
                trace("PRINT");
                System.out.println(pop());
                break;
            case FATAL:
                trace("FATAL");
                throw new Exception("FATAL bytecode executed at " + ip);
            
            case CONST:
                trace("CONST " + operands[0]);
                push(operands[0]);
                break;
            case POP:
                trace("POP");
                pop();
                break;

            // Binary math operations
            case ADD:
            {
                trace("ADD");
                // Left-to-right-pushed parameter order
                // means we extract in reverse order
                int rhs = pop();
                int lhs = pop();
                push(lhs + rhs);
                break;
            }
            case SUB:
            {
                trace("SUB");
                // Left-to-right-pushed parameter order
                // means we extract in reverse order
                int rhs = pop();
                int lhs = pop();
                push(lhs - rhs);
                break;
            }
            case MUL:
            {
                trace("MUL");
                // Left-to-right-pushed parameter order
                // means we extract in reverse order
                int rhs = pop();
                int lhs = pop();
                push(lhs * rhs);
                break;
            }
            case DIV:
            {
                trace("DIV");
                // Left-to-right-pushed parameter order
                // means we extract in reverse order
                int rhs = pop();
                int lhs = pop();
                push(lhs / rhs);
                break;
            }
            case MOD:
            {
                trace("ADD");
                // Left-to-right-pushed parameter order
                // means we extract in reverse order
                int rhs = pop();
                int lhs = pop();
                push(lhs % rhs);
                break;
            }
            // Unary math operations
            case ABS:
                trace("ABS");
                push(Math.abs(pop()));
                break;
            case NEG:
                trace("NEG");
                push(- pop());
                break;
            
            // Comparison ops
            case EQ:
            {
                trace("EQ");
                // Left-to-right-pushed parameter order
                // means we extract in reverse order
                int rhs = pop();
                int lhs = pop();
                push(lhs == rhs ? 1 : 0);
                break;
            }
            case NEQ:
            {
                trace("NEQ");
                // Left-to-right-pushed parameter order
                // means we extract in reverse order
                int rhs = pop();
                int lhs = pop();
                push(lhs != rhs ? 1 : 0);
                break;
            }
            case GT:
            {
                trace("GT");
                // Left-to-right-pushed parameter order
                // means we extract in reverse order
                int rhs = pop();
                int lhs = pop();
                push(lhs > rhs ? 1 : 0);
                break;
            }
            case LT:
            {
                trace("LT");
                // Left-to-right-pushed parameter order
                // means we extract in reverse order
                int rhs = pop();
                int lhs = pop();
                push(lhs < rhs ? 1 : 0);
                break;
            }
            case GTE:
            {
                trace("GTE");
                // Left-to-right-pushed parameter order
                // means we extract in reverse order
                int rhs = pop();
                int lhs = pop();
                push(lhs >= rhs ? 1 : 0);
                break;
            }
            case LTE:
            {
                trace("LTE");
                // Left-to-right-pushed parameter order
                // means we extract in reverse order
                int rhs = pop();
                int lhs = pop();
                push(lhs <= rhs ? 1 : 0);
                break;
            }

            // Branching ops
            case JMP:
            {
                trace("JMP " + operands[0]);
                ip = operands[0];
                break;
            }
            case RJMP:
            {
                trace("RJMP " + operands[0]);
                ip += operands[0];
                break;
            }
            case JMPI:
            {
                trace("JMPI");
                int location = pop();
                ip = location;
                break;
            }
            case RJMPI:
            {
                trace("RJMPI");
                int offset = pop();
                ip += offset;
                break;
            }
            case JZ:
            {
                trace("JZ " + operands[0]);
                int jump = pop();
                if (jump == 0) { 
                    ip = operands[0];
                }
                else {
                    ip += 2;
                }
                break;
            }
            case JNZ:
            {
                trace("JNZ " + operands[0]);
                int jump = pop();
                if (jump != 0) { 
                    ip = operands[0];
                }
                else {
                    ip += 2;
                }
                break;
            }

            // Globals
            //
            case GLOAD:
            {
                trace("GLOAD " + operands[0]);
                push(globals[operands[0]]);
                break;
            }
            case GSTORE:
            {
                trace("GSTORE " + operands[0]);
                globals[operands[0]] = pop();
                break;
            }
        }
    }
    int ip = 0;
    public void execute(int[] code) {
        for (ip = 0; ip < code.length; )
        {
            switch (code[ip])
            {
                case HALT:
                    trace("HALT at " + ip);
                    return;

                // 0-operand opcodes
                case NOP:
                case TRACE:
                case DUMP:
                case PRINT:
                case FATAL:
                case POP:
                case ADD:
                case SUB:
                case MUL:
                case DIV:
                case MOD:
                case ABS:
                case NEG:
                case EQ:
                case NEQ:
                case GT:
                case LT:
                case GTE:
                case LTE:
                    execute(code[ip]);
                    ip++;
                    break;

                case JMPI:
                case RJMPI:
                    execute(code[ip]);
                    // Do NOT adjust IP
                    break;
                    
                // 1-operand opcodes
                case CONST:
                case GLOAD:
                case GSTORE:
                    execute(code[ip], code[ip + 1]);
                    ip += 2;
                    break;

                case JMP:
                case RJMP:
                case JZ:
                case JNZ:
                    execute(code[ip], code[ip + 1]);
                    // Do NOT adjust IP
                    break;

                // 2-operand (or more) opcodes

                // Unknown
                default:
                    throw new Exception("Unrecognized opcode: " + code[ip]);
            }
        }
    }
}
