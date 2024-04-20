//
// Created by George Liontos on 20/4/24.
//

#include "unit_test.h"
#include "../virtual_machine.h"

UNIT_TEST(store) {
    VirtualMachine vm = {};
    Bytecode codes[] = {
            Bytecode::CONST, (Bytecode) 42,
            Bytecode::GSTORE, (Bytecode) 0
    };


    vm_execute(&vm, codes, ARRAY_SIZE(codes));

    ASSERT(vm.stack_pointer == -1);
    ASSERT(vm.globals[0] == 42);

    TEST_PASSED();
}

UNIT_TEST(load) {
    VirtualMachine vm = {};
    vm.globals[0] = 42;
    Bytecode codes[] = {
            Bytecode::GLOAD, (Bytecode) 0,
    };

    vm_execute(&vm, codes, ARRAY_SIZE(codes));

    ASSERT(vm.stack_pointer == 0);
    ASSERT(vm.globals[0] == 42);
    ASSERT(vm.stack[0] == 42);

    TEST_PASSED();
}

UNIT_TEST(load_and_store) {
    VirtualMachine vm = {};
    Bytecode codes[] = {
            Bytecode::CONST, (Bytecode) 42,
            Bytecode::GSTORE, (Bytecode) 0,
            Bytecode::CONST, (Bytecode) 3,
            Bytecode::GSTORE, (Bytecode) 1,
            Bytecode::GLOAD, (Bytecode) 0,
            Bytecode::GLOAD, (Bytecode) 1,
            Bytecode::ADD,
            Bytecode::GSTORE, (Bytecode) 2
    };

    vm_execute(&vm, codes, ARRAY_SIZE(codes));

    ASSERT(vm.stack_pointer == -1);
    ASSERT(vm.globals[0] == 42);
    ASSERT(vm.globals[1] == 3);
    ASSERT(vm.globals[2] == 45);

    TEST_PASSED();
}

TestFn tests[] = {
        test_store,
        test_load,
        test_load_and_store,
};

int main() {
    run_tests(tests, ARRAY_SIZE(tests));
    return 0;
}
