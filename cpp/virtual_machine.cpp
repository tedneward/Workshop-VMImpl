//
// Created by George Liontos on 19/4/24.
//

#include "common.h"
#include "virtual_machine.h"
#include "format_buffer.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <memory.h>

#define VM_BIN_OP(op)        \
do {                         \
    int rhs = vm_pop(vm);    \
    int lhs = vm_pop(vm);    \
    vm_push(vm, lhs op rhs); \
} while (0)

internal void format_vm_stack(VirtualMachine* vm, FormatBuffer* fmt_buf) {
    format_number_array(vm->stack, vm->stack_pointer + 1, fmt_buf);
}

internal void format_vm_globals(VirtualMachine* vm, FormatBuffer* fmt_buf) {
    format_number_array(vm->globals, ARRAY_SIZE(vm->globals), fmt_buf);
}

void vm_dump(VirtualMachine* vm) {
    FormatBuffer fmt_buf = {0};
    FormatBuffer_init(&fmt_buf, MAX(vm->stack_pointer + 1, 8));

    printf("SimpleVM - DUMP\n");
    printf("===============\n");
    printf("IP: %d / Trace: %s\n", vm->instruction_pointer, vm->trace ? "True" : "False");

    format_vm_stack(vm, &fmt_buf);
    printf("Working Stack (SP %d): %s\n", vm->stack_pointer, fmt_buf.buf);
    FormatBuffer_clear(&fmt_buf);

    format_vm_globals(vm, &fmt_buf);
    printf("Globals: %s\n", fmt_buf.buf);
    FormatBuffer_clear(&fmt_buf);

    printf("Call stack (FP: %d)\n", vm->frame_pointer);
    CallFrames* call_frames = &vm->call_frames;
    for (ssize_t i = call_frames->len - 1; i > -1; --i) {
        CallFrame* frame = &call_frames->frames[i];
        printf("  Call Frame %zd\n", i);
        printf("  +- Return address: %d\n", frame->return_address);
        format_number_array(frame->locals, ARRAY_SIZE(frame->locals), &fmt_buf);
        printf("  +- Locals: %s\n", fmt_buf.buf);
        FormatBuffer_clear(&fmt_buf);
        printf("  +------------------------------------");
    }

    FormatBuffer_free(&fmt_buf);
}

__attribute__((format(printf, 2, 3))) internal inline void vm_trace(VirtualMachine* vm, const char* fmt, ...) {
    if (vm->trace) {
        va_list args;
        va_start(args, fmt);
        vprintf(fmt, args);
        printf("\n");
        va_end(args);
    }
}

internal int32_t vm_pop(VirtualMachine* vm) {
    int res = vm->stack[vm->stack_pointer--];

    if (vm->trace) {
        FormatBuffer fmt_buf = allocate_and_format_number_array(vm->stack, vm->stack_pointer + 1);
        vm_trace(vm, "Pop --> Stack(SP: %d): %s", vm->stack_pointer, fmt_buf.buf);
        FormatBuffer_free(&fmt_buf);
    }

    return res;
}

internal void vm_push(VirtualMachine* vm, int operand) {
    vm->stack[++vm->stack_pointer] = operand;

    if (vm->trace) {
        FormatBuffer fmt_buf = allocate_and_format_number_array(vm->stack, vm->stack_pointer + 1);
        vm_trace(vm, "Push: %d --> Stack(SP: %d): %s", operand, vm->stack_pointer, fmt_buf.buf);
        FormatBuffer_free(&fmt_buf);
    }
}

internal void vm_push_call_frame(VirtualMachine* vm, CallFrame* call_frame) {
    CallFrames* call_frames = &vm->call_frames;

    if (call_frames->len == call_frames->capacity) {
        size_t new_capacity = MAX(call_frames->capacity, 8);
        CallFrame* new_frames = MALLOC(new_capacity, CallFrame);

        if (call_frames->frames) {
            memcpy(new_frames, call_frames->frames, call_frames->len * sizeof(CallFrame));
            free(call_frames->frames);
        }

        call_frames->frames = new_frames;
        call_frames->capacity = new_capacity;
    }

    call_frames->frames[call_frames->len] = *call_frame;
    ++call_frames->len;
}

internal void advance_vm_ip(VirtualMachine* vm, Bytecode code) {
    switch (code) {
        case Bytecode::JMP:
        case Bytecode::JMPI:
        case Bytecode::RJMP:
        case Bytecode::RJMPI:
        case Bytecode::JZ:
        case Bytecode::JNZ:
        case Bytecode::CALL:
        case Bytecode::RET:
            break;
        case Bytecode::NOP:
        case Bytecode::DUMP:
        case Bytecode::TRACE:
        case Bytecode::PRINT:
        case Bytecode::FATAL:
        case Bytecode::POP:
        case Bytecode::ADD:
        case Bytecode::SUB:
        case Bytecode::MUL:
        case Bytecode::DIV:
        case Bytecode::MOD:
        case Bytecode::ABS:
        case Bytecode::NEG:
        case Bytecode::EQ:
        case Bytecode::NEQ:
        case Bytecode::GT:
        case Bytecode::LT:
        case Bytecode::GTE:
        case Bytecode::LTE:
            ++vm->instruction_pointer;
            break;
        case Bytecode::CONST:
        case Bytecode::GSTORE:
        case Bytecode::GLOAD:
        case Bytecode::LOAD:
        case Bytecode::STORE:
            vm->instruction_pointer += 2;
            break;
        default:
            assert(false);
    }
}

void vm_execute(VirtualMachine* vm, Bytecode* codes, size_t num_codes) {
    for (vm->instruction_pointer = 0; vm->instruction_pointer != num_codes; ) {
        Bytecode code = codes[vm->instruction_pointer];
        switch (code) {
            case Bytecode::NOP:
                vm_trace(vm, "NOP");
                break;
            case Bytecode::DUMP:
                vm_trace(vm, "DUMP");
                vm_dump(vm);
                break;
            case Bytecode::TRACE:
                vm->trace = !vm->trace;
                vm_trace(vm, vm->trace ? "TRACE enabled" : "TRACE disabled");
                break;
            case Bytecode::PRINT:
            {
                vm_trace(vm, "PRINT");
                int32_t value = vm_pop(vm);
                printf("%d\n", value);
            } break;
            case Bytecode::HALT:
                vm_trace(vm, "HALT");
                return;
            case Bytecode::FATAL:
                abort();
            case Bytecode::CONST:
            {
                int32_t operand = (int32_t) codes[vm->instruction_pointer + 1];
                vm_trace(vm, "CONST %d", operand);
                vm_push(vm, operand);
            } break;
            case Bytecode::POP:
                vm_trace(vm, "POP");
                vm_pop(vm);
                break;
            case Bytecode::ADD:
                vm_trace(vm, "ADD");
                VM_BIN_OP(+);
                break;
            case Bytecode::SUB:
                vm_trace(vm, "SUB");
                VM_BIN_OP(-);
                break;
            case Bytecode::MUL:
                vm_trace(vm, "MUL");
                VM_BIN_OP(*);
                break;
            case Bytecode::DIV:
                vm_trace(vm, "DIV");
                VM_BIN_OP(/);
                break;
            case Bytecode::MOD:
                vm_trace(vm, "MOD");
                VM_BIN_OP(%);
                break;
            case Bytecode::ABS:
            {
                vm_trace(vm, "ABS");
                int32_t value = vm_pop(vm);
                vm_push(vm, ABS(value));
            } break;
            case Bytecode::NEG:
            {
                vm_trace(vm, "NEG");
                int32_t value = vm_pop(vm);
                vm_push(vm, -value);
            } break;
            case Bytecode::EQ:
                vm_trace(vm, "EQ");
                VM_BIN_OP(==);
                break;
            case Bytecode::NEQ:
                vm_trace(vm, "NEQ");
                VM_BIN_OP(!=);
                break;
            case Bytecode::GT:
                vm_trace(vm, "GT");
                VM_BIN_OP(>);
                break;
            case Bytecode::LT:
                vm_trace(vm, "LT");
                VM_BIN_OP(<);
                break;
            case Bytecode::GTE:
                vm_trace(vm,"GTE");
                VM_BIN_OP(>=);
                break;
            case Bytecode::LTE:
                vm_trace(vm, "LTE");
                VM_BIN_OP(<=);
                break;
            case Bytecode::JMP:
            {
                int32_t operand = (int32_t) codes[vm->instruction_pointer + 1];
                vm_trace(vm, "JMP %d", operand);
                vm->instruction_pointer = operand;
            } break;
            case Bytecode::RJMP:
            {
                int32_t operand = (int32_t) codes[vm->instruction_pointer + 1];
                vm_trace(vm, "RJMP %d", operand);
                vm->instruction_pointer += operand;
            } break;
            case Bytecode::JMPI:
            {
                int32_t location = vm_pop(vm);
                vm_trace(vm, "JMPI %d", location);
                vm->instruction_pointer = location;
            } break;
            case Bytecode::RJMPI:
            {
                int32_t location = vm_pop(vm);
                vm_trace(vm, "RJMPI %d", location);
                vm->instruction_pointer += location;
            } break;
            case Bytecode::JZ:
            {
                int32_t operand = (int32_t) codes[vm->instruction_pointer + 1];
                vm_trace(vm, "JZ %d", operand);
                if (vm_pop(vm) == 0) {
                    vm->instruction_pointer = operand;
                } else {
                    vm->instruction_pointer += 2;
                }
            } break;
            case Bytecode::JNZ:
            {
                int32_t operand = (int32_t) codes[vm->instruction_pointer + 1];
                vm_trace(vm, "JNZ %d", operand);
                if (vm_pop(vm) != 0) {
                    vm->instruction_pointer = operand;
                } else {
                    vm->instruction_pointer += 2;
                }
            } break;
            case Bytecode::GSTORE:
            {
                int32_t index = (int32_t) codes[vm->instruction_pointer + 1];
                vm_trace(vm, "GSTORE %d", index);
                vm->globals[index] = vm_pop(vm);
            } break;
            case Bytecode::GLOAD:
            {
                int32_t index = (int32_t) codes[vm->instruction_pointer + 1];
                vm_trace(vm, "GLOAD %d", index);
                vm_push(vm, vm->globals[index]);
            } break;
            case Bytecode::CALL:
            {
                int32_t operand = (int32_t) codes[vm->instruction_pointer + 1];
                vm_trace(vm, "CALL %d", operand);

                CallFrame new_frame = {};
                new_frame.return_address = vm->instruction_pointer + 2;
                vm_push_call_frame(vm, &new_frame);
                ++vm->frame_pointer;

                vm->instruction_pointer = operand;
            } break;
            case Bytecode::RET:
                vm_trace(vm, "RET");
                vm->instruction_pointer = vm->call_frames.frames[vm->frame_pointer].return_address;
                --vm->call_frames.len;
                --vm->frame_pointer;
                break;
            case Bytecode::STORE:
            {
                int32_t index = (int32_t) codes[vm->instruction_pointer + 1];
                vm_trace(vm, "STORE %d", index);
                vm->call_frames.frames[vm->frame_pointer].locals[index] = vm_pop(vm);
            }  break;
            case Bytecode::LOAD:
            {
                int32_t index = (int32_t) codes[vm->instruction_pointer + 1];
                vm_trace(vm, "LOAD %d", index);
                int32_t local_value = vm->call_frames.frames[vm->frame_pointer].locals[index];
                vm_push(vm, local_value);
            } break;
        }

        advance_vm_ip(vm, code);
    }
}
