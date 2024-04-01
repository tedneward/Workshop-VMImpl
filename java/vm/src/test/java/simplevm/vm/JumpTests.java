package simplevm.vm;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

import static simplevm.vm.Bytecode.*;

public class JumpTests {
    @Test void testJMP() {
        VirtualMachine vm = new VirtualMachine();
        vm.execute(new int[] {
            /* 0*/ JMP, 3,  // bypass FATAL opcode
            /* 2*/ FATAL,
            /* 3*/ NOP
        });

        assertEquals(0, vm.getStack().length);
    }
    @Test void testRJMP() {
        VirtualMachine vm = new VirtualMachine();
        vm.execute(new int[] {
            /* 0*/ RJMP, 6,  // JMP to current IP (0) + 6 ==> 6
            /* 2*/ CONST, 12,
            /* 4*/ FATAL,
            /* 5*/ FATAL,
            /* 6*/ NOP
        });

        assertEquals(0, vm.getStack().length);
    }

    @Test void testJMPI() {
        VirtualMachine vm = new VirtualMachine();
        vm.execute(new int[] {
            /* 0*/ CONST, 7,
            /* 2*/ JMPI,    // JMP to 7, which should bypass all CONSTS
            /* 3*/ CONST, 12,
            /* 5*/ CONST, 27,
            /* 7*/ NOP
        });

        assertEquals(0, vm.getStack().length);
    }

    @Test void testRJMPI()
    {
        VirtualMachine vm = new VirtualMachine();

        // CONST and FATALs here should be bypassed...
        vm.execute(new int[] {
            /* 0*/ CONST, 5,
            /* 2*/ RJMPI, // Jump to current IP (2) + 5 => 7
            /* 3*/ CONST, 12,
            /* 5*/ FATAL,
            /* 6*/ FATAL,
            /* 7*/ NOP
        });

        // ... leaving nothing on the stack
        assertEquals(0, vm.getStack().length);
    }

    @Test void testLotsofJumps() {
        VirtualMachine vm = new VirtualMachine();
        vm.execute(new int[] {
            /* 0*/ TRACE,
            /* 1*/ JMP, 4,  // bypass FATAL opcode
            /* 3*/ FATAL,
            /* 4*/ JMP, 7,
            /* 6*/ FATAL,
            /* 7*/ JMP, 10,
            /* 9*/ FATAL,
            /*10*/ NOP
        });

        assertEquals(0, vm.getStack().length);
    }
}
