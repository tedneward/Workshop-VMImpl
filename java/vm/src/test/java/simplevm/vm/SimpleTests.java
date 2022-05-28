package simplevm.vm;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

class SimpleTests {
    @Test void testTest() {
        assertEquals(2, 1 + 1);
        //assertEquals(2, 1 - 1); // just to fail-test, just in case
    }
    @Test void testInstantiation() {
        VirtualMachine vm = new VirtualMachine();

        assertTrue(vm != null);
    }
    @Test void testNOP() {
        VirtualMachine vm = new VirtualMachine();

        Bytecode[] code = {
            Bytecode.NOP
        };
        vm.execute(code);

        // If we got here, with no exception, we're good
        assertTrue(true);
    }
    @Test void testNOPs() {
        VirtualMachine vm = new VirtualMachine();

        Bytecode[] code = {
            Bytecode.NOP,
            Bytecode.NOP,
            Bytecode.NOP,
            Bytecode.NOP
        };
        vm.execute(code);

        // If we got here, with no exception, we're good
        assertTrue(true);
    }
    @Test void testDump() {
        VirtualMachine vm = new VirtualMachine();

        Bytecode[] code = {
            Bytecode.NOP,
            Bytecode.DUMP
        };
        vm.execute(code);

        // If we got here, with no exception, we're good
        assertTrue(true);
    }
    @Test void testTrace() {
        VirtualMachine vm = new VirtualMachine();

        Bytecode[] code = {
            Bytecode.TRACE,
            Bytecode.NOP,
            Bytecode.DUMP
        };
        vm.execute(code);

        // If we got here, with no exception, we're good
        assertTrue(true);
    }
}
