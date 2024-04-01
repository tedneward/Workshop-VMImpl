package simplevm.vm;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.BeforeEach;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import static simplevm.vm.Bytecode.*;

/*
 * There's a TON more tests we should be doing here to get even reasonably
 * close to a feeling of safety and goodness when it comes to this code,
 * but that's left as an exercise to the workshop participant. :-)
 */
public class MathTests {

    @BeforeEach public void newVM() { vm = new VirtualMachine(); }
    public VirtualMachine vm = null;

    @Test public void add() {
        vm.execute(new int[] {
            CONST, 5,
            CONST, 5,
            ADD
        });

        assertEquals(1, vm.getStack().length);
        assertEquals(10, vm.getStack()[0]);
    }

    @Test public void sub() {
        vm.execute(new int[] {
            CONST, 15,
            CONST, 5,
            SUB
        });

        assertEquals(1, vm.getStack().length);
        assertEquals(10, vm.getStack()[0]);
    }

    @Test public void mul() {
        vm.execute(new int[] {
            CONST, 2,
            CONST, 5,
            MUL
        });

        assertEquals(1, vm.getStack().length);
        assertEquals(10, vm.getStack()[0]);
    }

    @Test public void div() {
        vm.execute(new int[] {
            CONST, 50,
            CONST, 5,
            DIV
        });

        assertEquals(1, vm.getStack().length);
        assertEquals(10, vm.getStack()[0]);
    }

    @Test public void mod() {
        vm.execute(new int[] {
            CONST, 30,
            CONST, 20,
            MOD
        });

        assertEquals(1, vm.getStack().length);
        assertEquals(10, vm.getStack()[0]);
    }

    @Test public void abs() {
        vm.execute(new int[] {
            CONST, -10,
            ABS
        });

        assertEquals(1, vm.getStack().length);
        assertEquals(10, vm.getStack()[0]);
    }
    @Test public void neg() {
        vm.execute(new int[] {
            CONST, 10,
            NEG
        });

        assertEquals(1, vm.getStack().length);
        assertEquals(-10, vm.getStack()[0]);

        vm.execute(NEG);
        assertEquals(1, vm.getStack().length);
        assertEquals(10, vm.getStack()[0]);
    }
}
