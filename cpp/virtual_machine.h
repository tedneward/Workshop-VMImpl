//
// Created by George Liontos on 19/4/24.
//

#ifndef CPP_VIRTUAL_MACHINE_H
#define CPP_VIRTUAL_MACHINE_H

#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>

#define VM_STACK_SIZE 200
#define VM_GLOBALS_SIZE 32
#define VM_LOCALS_SIZE 32

enum class Bytecode: int32_t {
    NOP,
    DUMP,
    TRACE,
    PRINT,
    HALT,
    FATAL,

    // Stack opcodes
    CONST,
    POP,

    // Math opcodes (binary)
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,

    // Math opcodes (unary)
    ABS,
    NEG,

    // Comparison
    EQ,
    NEQ,
    GT,
    LT,
    GTE,
    LTE,

    // Branching opcodes
    JMP,
    JMPI,
    RJMP,
    RJMPI,
    JZ,
    JNZ,

    // Globals
    GSTORE,
    GLOAD,

    // Procedures/locals
    CALL,
    RET,
    LOAD,
    STORE
};

struct CallFrame {
    int32_t return_address = -1;
    int32_t locals[VM_LOCALS_SIZE] = {0};
};

struct CallFrames {
    CallFrame* frames = nullptr;
    ssize_t len = 0U;
    size_t capacity = 0U;
};

struct VirtualMachine {
    int32_t instruction_pointer = -1;
    int32_t stack_pointer = -1;
    int32_t frame_pointer = -1;
    CallFrames call_frames = {};
    int32_t stack[VM_STACK_SIZE] = {0};
    int32_t globals[VM_GLOBALS_SIZE] = {0};
    bool trace = false;
};

void vm_dump(VirtualMachine* vm);
void vm_execute(VirtualMachine* vm, Bytecode* codes, size_t num_codes);

#endif //CPP_VIRTUAL_MACHINE_H
