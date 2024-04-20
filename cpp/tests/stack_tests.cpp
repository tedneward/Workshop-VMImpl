//
// Created by George Liontos on 20/4/24.
//

#include "unit_test.h"
#include "../virtual_machine.h"

UNIT_TEST(pop) {
    VirtualMachine vm = {};
    Bytecode push_codes[] = {
        Bytecode::CONST, (Bytecode) 27
    };

    vm_execute(&vm, push_codes, ARRAY_SIZE(push_codes));

    ASSERT(vm.stack_pointer == 0);
    ASSERT(vm.stack[0] == 27);

    Bytecode pop = Bytecode::POP;
    vm_execute(&vm, &pop, 1);

    ASSERT(vm.stack_pointer == -1);

    TEST_PASSED();
}

UNIT_TEST(const) {
    VirtualMachine vm = {};
    Bytecode push_codes[] = {
            Bytecode::CONST, (Bytecode) 27,
            Bytecode::CONST, (Bytecode) 34
    };

    vm_execute(&vm, push_codes, ARRAY_SIZE(push_codes));

    ASSERT(vm.stack_pointer == 1);
    ASSERT(vm.stack[0] == 27);
    ASSERT(vm.stack[1] == 34);

    TEST_PASSED();
}

UNIT_TEST(const_pop) {
    VirtualMachine vm = {};
    Bytecode push_codes[] = {
            Bytecode::CONST, (Bytecode) 27,
            Bytecode::POP,
    };

    vm_execute(&vm, push_codes, ARRAY_SIZE(push_codes));

    ASSERT(vm.stack_pointer == -1);

    TEST_PASSED();
}


TestFn tests[] = {
        test_pop,
        test_const,
        test_const_pop,
};

int main() {
    run_tests(tests, ARRAY_SIZE(tests));
    return 0;
}
