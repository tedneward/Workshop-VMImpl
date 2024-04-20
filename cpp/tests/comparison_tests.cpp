//
// Created by George Liontos on 20/4/24.
//

#include "unit_test.h"
#include "../virtual_machine.h"

UNIT_TEST(eq) {
    VirtualMachine vm = {};
    Bytecode codes[] = {
            Bytecode::CONST, (Bytecode) 5,
            Bytecode::CONST, (Bytecode) 5,
            Bytecode::EQ
    };

    vm_execute(&vm, codes, ARRAY_SIZE(codes));

    ASSERT(vm.stack_pointer == 0);
    ASSERT(vm.stack[0] == 1);

    TEST_PASSED();
}

UNIT_TEST(neq) {
    VirtualMachine vm = {};
    Bytecode codes[] = {
            Bytecode::CONST, (Bytecode) 5,
            Bytecode::CONST, (Bytecode) 5,
            Bytecode::NEQ
    };

    vm_execute(&vm, codes, ARRAY_SIZE(codes));

    ASSERT(vm.stack_pointer == 0);
    ASSERT(vm.stack[0] == 0);

    TEST_PASSED();
}

UNIT_TEST(gt) {
    VirtualMachine vm = {};
    Bytecode codes[] = {
            Bytecode::CONST, (Bytecode) 2,
            Bytecode::CONST, (Bytecode) 5,
            Bytecode::GT
    };

    vm_execute(&vm, codes, ARRAY_SIZE(codes));

    ASSERT(vm.stack_pointer == 0);
    ASSERT(vm.stack[0] == 0);

    TEST_PASSED();
}

UNIT_TEST(lt) {
    VirtualMachine vm = {};
    Bytecode codes[] = {
            Bytecode::CONST, (Bytecode) 2,
            Bytecode::CONST, (Bytecode) 5,
            Bytecode::LT
    };

    vm_execute(&vm, codes, ARRAY_SIZE(codes));

    ASSERT(vm.stack_pointer == 0);
    ASSERT(vm.stack[0] == 1);

    TEST_PASSED();
}

UNIT_TEST(gte) {
    VirtualMachine vm = {};
    Bytecode codes[] = {
            Bytecode::CONST, (Bytecode) 5,
            Bytecode::CONST, (Bytecode) 5,
            Bytecode::GTE
    };

    vm_execute(&vm, codes, ARRAY_SIZE(codes));

    ASSERT(vm.stack_pointer == 0);
    ASSERT(vm.stack[0] == 1);

    TEST_PASSED();
}

UNIT_TEST(lte) {
    VirtualMachine vm = {};
    Bytecode codes[] = {
            Bytecode::CONST, (Bytecode) 5,
            Bytecode::CONST, (Bytecode) 5,
            Bytecode::LTE
    };

    vm_execute(&vm, codes, ARRAY_SIZE(codes));

    ASSERT(vm.stack_pointer == 0);
    ASSERT(vm.stack[0] == 1);

    TEST_PASSED();
}

TestFn tests[] = {
        test_eq,
        test_neq,
        test_gt,
        test_lt,
        test_gte,
        test_lte
};

int main() {
    run_tests(tests, ARRAY_SIZE(tests));
    return 0;
}
