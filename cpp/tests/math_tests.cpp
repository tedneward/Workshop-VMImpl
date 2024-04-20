//
// Created by George Liontos on 20/4/24.
//

#include "unit_test.h"
#include "../virtual_machine.h"

UNIT_TEST(add) {
    VirtualMachine vm = {};
    Bytecode codes[] = {
            Bytecode::CONST, (Bytecode) 5,
            Bytecode::CONST, (Bytecode) 5,
            Bytecode::ADD
    };

    vm_execute(&vm, codes, ARRAY_SIZE(codes));

    ASSERT(vm.stack_pointer == 0);
    ASSERT(vm.stack[0] == 10);

    TEST_PASSED();
}

UNIT_TEST(sub) {
    VirtualMachine vm = {};
    Bytecode codes[] = {
            Bytecode::CONST, (Bytecode) 15,
            Bytecode::CONST, (Bytecode) 5,
            Bytecode::SUB
    };

    vm_execute(&vm, codes, ARRAY_SIZE(codes));

    ASSERT(vm.stack_pointer == 0);
    ASSERT(vm.stack[0] == 10);

    TEST_PASSED();
}

UNIT_TEST(mul) {
    VirtualMachine vm = {};
    Bytecode codes[] = {
            Bytecode::CONST, (Bytecode) 2,
            Bytecode::CONST, (Bytecode) 5,
            Bytecode::MUL
    };

    vm_execute(&vm, codes, ARRAY_SIZE(codes));

    ASSERT(vm.stack_pointer == 0);
    ASSERT(vm.stack[0] == 10);

    TEST_PASSED();
}

UNIT_TEST(div) {
    VirtualMachine vm = {};
    Bytecode codes[] = {
            Bytecode::CONST, (Bytecode) 50,
            Bytecode::CONST, (Bytecode) 5,
            Bytecode::DIV
    };

    vm_execute(&vm, codes, ARRAY_SIZE(codes));

    ASSERT(vm.stack_pointer == 0);
    ASSERT(vm.stack[0] == 10);

    TEST_PASSED();
}

UNIT_TEST(mod) {
    VirtualMachine vm = {};
    Bytecode codes[] = {
            Bytecode::CONST, (Bytecode) 30,
            Bytecode::CONST, (Bytecode) 20,
            Bytecode::MOD
    };

    vm_execute(&vm, codes, ARRAY_SIZE(codes));

    ASSERT(vm.stack_pointer == 0);
    ASSERT(vm.stack[0] == 10);

    TEST_PASSED();
}

UNIT_TEST(abs) {
    VirtualMachine vm = {};
    Bytecode codes[] = {
            Bytecode::CONST, (Bytecode) -10,
            Bytecode::ABS
    };

    vm_execute(&vm, codes, ARRAY_SIZE(codes));

    ASSERT(vm.stack_pointer == 0);
    ASSERT(vm.stack[0] == 10);

    TEST_PASSED();
}

UNIT_TEST(neg) {
    VirtualMachine vm = {};
    Bytecode codes[] = {
            Bytecode::CONST, (Bytecode) 10,
            Bytecode::NEG
    };

    vm_execute(&vm, codes, ARRAY_SIZE(codes));

    ASSERT(vm.stack_pointer == 0);
    ASSERT(vm.stack[0] == -10);

    Bytecode neg = Bytecode::NEG;
    vm_execute(&vm, &neg, 1);

    ASSERT(vm.stack_pointer == 0);
    ASSERT(vm.stack[0] == 10);

    TEST_PASSED();
}

TestFn tests[] = {
        test_add,
        test_sub,
        test_mul,
        test_div,
        test_mod,
        test_abs,
        test_neg,
};

int main() {
    run_tests(tests, ARRAY_SIZE(tests));
    return 0;
}

