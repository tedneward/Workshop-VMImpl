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
}
