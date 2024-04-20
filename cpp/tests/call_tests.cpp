//
// Created by George Liontos on 20/4/24.
//

#include "unit_test.h"
#include "../virtual_machine.h"

UNIT_TEST(simple_call) {
    VirtualMachine vm = {};
    Bytecode codes[] = {
            // 0: entrypoint
            /* 0*/ Bytecode::TRACE,
            /* 1*/ Bytecode::CALL, (Bytecode) 5,
            /* 3*/ Bytecode::JMP, (Bytecode) 10,
            // 5: a simple print(12) function
            /* 5*/ Bytecode::CONST, (Bytecode) 12,
            /* 6*/ Bytecode::PRINT,
            /* 7*/ Bytecode::RET,
            // 8: end
            /* 8*/ Bytecode::NOP,
            /* 9*/ Bytecode::NOP,
            /*10*/ Bytecode::NOP
    };

    vm_execute(&vm, codes, ARRAY_SIZE(codes));

    ASSERT(vm.stack_pointer == -1);

    TEST_PASSED();
}

UNIT_TEST(countdown_function) {
    VirtualMachine vm = {};
    Bytecode codes[] = {
            // 0: entrypoint
            /* 0*/ Bytecode::TRACE,
            /* 1*/ Bytecode::JMP, (Bytecode) 25,
            // function countdown(count)
            //    expects count on top of stack; no return value
            /* 3*/ Bytecode::STORE, (Bytecode) 0,   // move count into locals[0]
            /* 5*/ Bytecode::LOAD, (Bytecode) 0,    // locals[0]
            /* 7*/ Bytecode::PRINT,      // print
            /* 8*/ Bytecode::LOAD, (Bytecode) 0,    // locals[0]
            /*10*/ Bytecode::CONST, (Bytecode) 0,   // 0
            /*12*/ Bytecode::EQ,         // locals[0] == 0 ?
            /*13*/ Bytecode::JNZ, (Bytecode) 24,    // jump to return
            /*15*/ Bytecode::LOAD, (Bytecode) 0,    // locals[0] = locals[0] - 1
            /*17*/ Bytecode::CONST, (Bytecode) 1,
            /*19*/ Bytecode::SUB,
            /*20*/ Bytecode::STORE, (Bytecode) 0,
            /*22*/ Bytecode::JMP, (Bytecode) 5,     // jump to top of loop
            /*24*/ Bytecode::RET,
            // end
            /*25*/ Bytecode::CONST, (Bytecode) 5,
            /*27*/ Bytecode::CALL, (Bytecode) 3,    // CALL line 3
            /*29*/ Bytecode::NOP
    };

    vm_execute(&vm, codes, ARRAY_SIZE(codes));

    ASSERT(vm.stack_pointer == -1);
    TEST_PASSED();
}

TestFn tests[] = {
        test_simple_call,
        test_countdown_function,
};

int main() {
    run_tests(tests, ARRAY_SIZE(tests));
    return 0;
}
