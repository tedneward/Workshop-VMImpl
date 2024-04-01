package simplevm.vm;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import static simplevm.vm.Bytecode.*;

public class GlobalTests {
    @Test void testStore() {
        VirtualMachine vm = new VirtualMachine();

        vm.execute(new int[] {
            CONST, 42,
            GSTORE, 0
        });

        assertEquals(0, vm.getStack().length);
        assertEquals(42, vm.getGlobals()[0]);
    }
    @Test void testLoad() {
        VirtualMachine vm = new VirtualMachine();

        vm.getGlobals()[0] = 12;
        vm.execute(new int[] {
            GLOAD, 0
        });

        // If we got here, with no exception, we're good
        assertEquals(1, vm.getStack().length);
        assertEquals(12, vm.getGlobals()[0]);
    }
    @Test void testLoadAndStore() {
        VirtualMachine vm = new VirtualMachine();

        vm.execute(new int[] {
            CONST, 42,
            GSTORE, 0,
            CONST, 3,
            GSTORE, 1,
            GLOAD, 0,
            GLOAD, 1,
            ADD,
            GSTORE, 2
        });

        assertEquals(0, vm.getStack().length);
        assertEquals(42, vm.getGlobals()[0]);
        assertEquals(3, vm.getGlobals()[1]);
        assertEquals(45, vm.getGlobals()[2]);
    }
}
