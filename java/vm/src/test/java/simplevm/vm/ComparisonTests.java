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
public class ComparisonTests {
    @BeforeEach public void newVM() { vm = new VirtualMachine(); }
    public VirtualMachine vm = null;

    @Test public void eq() {
        vm.execute(new int[] {
            CONST, 5,
            CONST, 5,
            EQ
        });

        assertEquals(1, vm.getStack().length);
        assertEquals(1, vm.getStack()[0]); // 5 == 5? Yes!
    }
    @Test public void neq() {
        vm.execute(new int[] {
            CONST, 5,
            CONST, 5,
            NEQ
        });

        assertEquals(1, vm.getStack().length);
        assertEquals(0, vm.getStack()[0]); // 5 != 5? No!
    }
    @Test public void gt() {
        vm.execute(new int[] {
            CONST, 2,
            CONST, 5,
            GT
        });

        assertEquals(1, vm.getStack().length);
        assertEquals(0, vm.getStack()[0]); // 2 > 5? No!
    }
    @Test public void lt() {
        vm.execute(new int[] {
            CONST, 2,
            CONST, 5,
            LT
        });

        assertEquals(1, vm.getStack().length);
        assertEquals(1, vm.getStack()[0]); // 2 < 5? Yes!
    }
}
