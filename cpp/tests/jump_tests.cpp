//
// Created by George Liontos on 20/4/24.
//

#include "unit_test.h"
#include "../virtual_machine.h"

UNIT_TEST(jmp) {
    VirtualMachine vm = {};
    Bytecode codes[] = {
            Bytecode::JMP, (Bytecode) 3,
            Bytecode::FATAL,
            Bytecode::NOP,
    };

    vm_execute(&vm, codes, ARRAY_SIZE(codes));

    ASSERT(vm.stack_pointer == -1);

    TEST_PASSED();
}

UNIT_TEST(rjmp) {
    VirtualMachine vm = {};
    Bytecode codes[] = {
            Bytecode::RJMP, (Bytecode) 6,
            Bytecode::CONST, (Bytecode) 12,
            Bytecode::FATAL,
            Bytecode::FATAL,
            Bytecode::NOP,
    };

    vm_execute(&vm, codes, ARRAY_SIZE(codes));

    ASSERT(vm.stack_pointer == -1);

    TEST_PASSED();
}

UNIT_TEST(jmpi) {
    VirtualMachine vm = {};
    Bytecode codes[] = {
            Bytecode::CONST, (Bytecode) 7,
            Bytecode::JMPI,
            Bytecode::CONST, (Bytecode) 12,
            Bytecode::CONST, (Bytecode) 27,
            Bytecode::NOP,
    };

    vm_execute(&vm, codes, ARRAY_SIZE(codes));

    ASSERT(vm.stack_pointer == -1);

    TEST_PASSED();
}

UNIT_TEST(rjmpi) {
    VirtualMachine vm = {};
    Bytecode codes[] = {
            Bytecode::CONST, (Bytecode) 5,
            Bytecode::RJMPI,
            Bytecode::CONST, (Bytecode) 12,
            Bytecode::FATAL,
            Bytecode::FATAL,
            Bytecode::NOP,
    };

    vm_execute(&vm, codes, ARRAY_SIZE(codes));

    ASSERT(vm.stack_pointer == -1);

    TEST_PASSED();
}

UNIT_TEST(jnz) {
    VirtualMachine vm = {};
    Bytecode codes[] = {
            Bytecode::CONST, (Bytecode) 5,
            Bytecode::JNZ, (Bytecode) 6,
            Bytecode::FATAL,
            Bytecode::FATAL,
            Bytecode::NOP,
    };

    vm_execute(&vm, codes, ARRAY_SIZE(codes));

    ASSERT(vm.stack_pointer == -1);

    TEST_PASSED();
}

UNIT_TEST(jz) {
    VirtualMachine vm = {};
    Bytecode codes[] = {
            Bytecode::CONST, (Bytecode) 0,
            Bytecode::JZ, (Bytecode) 6,
            Bytecode::FATAL,
            Bytecode::FATAL,
            Bytecode::NOP,
    };

    vm_execute(&vm, codes, ARRAY_SIZE(codes));

    ASSERT(vm.stack_pointer == -1);

    TEST_PASSED();
}

UNIT_TEST(many_jumps) {
    VirtualMachine vm = {};
    Bytecode codes[] = {
            Bytecode::TRACE,
            Bytecode::JMP, (Bytecode) 4,
            Bytecode::FATAL,
            Bytecode::JMP, (Bytecode) 7,
            Bytecode::FATAL,
            Bytecode::JMP, (Bytecode) 10,
            Bytecode::FATAL,
            Bytecode::NOP,
    };

    vm_execute(&vm, codes, ARRAY_SIZE(codes));

    ASSERT(vm.stack_pointer == -1);

    TEST_PASSED();
}

TestFn tests[] = {
        test_jmp,
        test_jmpi,
        test_rjmp,
        test_rjmpi,
        test_jnz,
        test_jz,
        test_many_jumps,
};

int main() {
    run_tests(tests, ARRAY_SIZE(tests));
    return 0;
}
