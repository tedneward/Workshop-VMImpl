package simplevm.vm;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import static simplevm.vm.Bytecode.*;

public class StackTests {
    @Test void testPushPop() {
        VirtualMachine vm = new VirtualMachine();

        vm.push(27);

        assertEquals(1, vm.getStack().length);
        assertEquals(27, vm.getStack()[0]);

        int value = vm.pop();
        assertEquals(27, value);
        assertEquals(0, vm.getStack().length);
    }
    @Test void TestCONST()
    {
        VirtualMachine vm = new VirtualMachine();

        vm.execute(CONST, 34);
        vm.execute(new int[] {
            CONST, 27,
        });

        assertEquals(2, vm.getStack().length);
        assertEquals(34, vm.getStack()[0]);
        assertEquals(27, vm.getStack()[1]);
    }
    @Test void TestCONSTPOP()
    {
        VirtualMachine vm = new VirtualMachine();

        vm.execute(new int[] {
            CONST, 27,
            POP,
        });

        assertEquals(0, vm.getStack().length);
    }
}