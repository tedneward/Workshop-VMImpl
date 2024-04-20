//
// Created by George Liontos on 20/4/24.
//

#include "cli.h"
#include "common.h"
#include "entire_file.h"

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <memory.h>
#include <sys/types.h>

#define BYTECODE_ITEM(name, has_operand) {#name, Bytecode::name, has_operand}
#define BYTECODE_ITEM_NO_OPERAND(name) BYTECODE_ITEM(name, false)
#define BYTECODE_ITEM_WITH_OPERAND(name) BYTECODE_ITEM(name, true)

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

struct BytecodeItem {
    const char* name;
    Bytecode value;
    bool accepts_value;
};

static const BytecodeItem bytecode_items[] = {
        BYTECODE_ITEM_NO_OPERAND(NOP),
        BYTECODE_ITEM_NO_OPERAND(DUMP),
        BYTECODE_ITEM_NO_OPERAND(TRACE),
        BYTECODE_ITEM_NO_OPERAND(HALT),
        BYTECODE_ITEM_NO_OPERAND(FATAL),
        BYTECODE_ITEM_WITH_OPERAND(CONST),
        BYTECODE_ITEM_NO_OPERAND(POP),
        BYTECODE_ITEM_NO_OPERAND(ADD),
        BYTECODE_ITEM_NO_OPERAND(SUB),
        BYTECODE_ITEM_NO_OPERAND(MUL),
        BYTECODE_ITEM_NO_OPERAND(DIV),
        BYTECODE_ITEM_NO_OPERAND(MOD),
        BYTECODE_ITEM_NO_OPERAND(ABS),
        BYTECODE_ITEM_NO_OPERAND(NEG),
        BYTECODE_ITEM_NO_OPERAND(EQ),
        BYTECODE_ITEM_NO_OPERAND(NEQ),
        BYTECODE_ITEM_NO_OPERAND(GT),
        BYTECODE_ITEM_NO_OPERAND(LT),
        BYTECODE_ITEM_NO_OPERAND(GTE),
        BYTECODE_ITEM_NO_OPERAND(LTE),
        BYTECODE_ITEM_WITH_OPERAND(JMP),
        BYTECODE_ITEM_NO_OPERAND(JMPI),
        BYTECODE_ITEM_WITH_OPERAND(RJMP),
        BYTECODE_ITEM_NO_OPERAND(RJMPI),
        BYTECODE_ITEM_WITH_OPERAND(JZ),
        BYTECODE_ITEM_WITH_OPERAND(JNZ),
        BYTECODE_ITEM_WITH_OPERAND(GSTORE),
        BYTECODE_ITEM_WITH_OPERAND(GLOAD),
        BYTECODE_ITEM_WITH_OPERAND(CALL),
        BYTECODE_ITEM_NO_OPERAND(RET),
        BYTECODE_ITEM_WITH_OPERAND(LOAD),
        BYTECODE_ITEM_WITH_OPERAND(STORE),
};

struct BytecodeBuffer {
    Bytecode* buf = nullptr;
    size_t len = 0U;
    size_t capacity = 0U;
};

static void BytecodeBuffer_init(BytecodeBuffer* buffer, size_t capacity) {
    buffer->buf = MALLOC(capacity, Bytecode);
    buffer->len = 0U;
    buffer->capacity = capacity;
}

static void BytecodeBuffer_push(BytecodeBuffer* buffer, Bytecode code) {
    if (buffer->len == buffer->capacity) {
        Bytecode* new_buf = MALLOC(buffer->capacity * 2, Bytecode);
        memcpy(new_buf, buffer->buf, buffer->capacity * sizeof(Bytecode));
        free(buffer->buf);
        buffer->buf = new_buf;
        buffer->capacity *= 2;
    }

    buffer->buf[buffer->len++] = code;
}

struct Lexer {
    char* stream;
    size_t len;
    size_t cursor = 0;
    size_t line_no = 1;
};

static void Lexer_skip_whitespace(Lexer* lexer) {
    while (lexer->cursor != lexer->len && isspace(lexer->stream[lexer->cursor])) {
        ++lexer->cursor;
        if (lexer->stream[0] == '\n') {
            ++lexer->line_no;
        }
    }
}

struct Token {
    char* token;
    size_t token_len;
};

static Token Lexer_next_token(Lexer* lexer) {
    if (lexer->cursor == lexer->len) {
        return (Token) {0};
    }

    Lexer_skip_whitespace(lexer);
    char* token_start = &lexer->stream[lexer->cursor];
    size_t cursor_start = lexer->cursor;
    while (lexer->cursor != lexer->len && !isspace(lexer->stream[lexer->cursor])) {
        ++lexer->cursor;
    }

    Token res = {0};
    res.token = token_start;
    res.token_len = lexer->cursor - cursor_start;
    return res;
}

static bool parse_int(Token token, int32_t* res) {
    assert(token.token);
    int32_t result = 0;
    size_t i = 0U;

    int32_t sign = 1;
    if (token.token[0] == '-') {
        sign = -1;
        ++i;
    }

    for (; i != token.token_len; ++i) {
        if (isdigit(token.token[i])) {
            result = result * 10 + (token.token[i] - '0');
        } else {
            return false;
        }
    }

    result *= sign;
    *res = result;

    return true;
}

static bool compile_input(const char* path, BytecodeBuffer* out_buffer) {
    EntireFile file = read_entire_file_into_memory(path);
    if (!file.contents) {
        return false;
    }

    Lexer lexer = {};
    lexer.stream = file.contents;
    lexer.len = file.num_bytes;

    for (;;) {
        Token next = Lexer_next_token(&lexer);
        if (!next.token) {
            break;
        }

        ssize_t bytecode_item_index = -1;
        for (size_t i = 0U; i != ARRAY_SIZE(bytecode_items); ++i) {
            BytecodeItem bytecode_item = bytecode_items[i];
            if (strncmp(next.token, bytecode_item.name, next.token_len) == 0) {
                bytecode_item_index = i;
                break;
            }
        }

        if (bytecode_item_index == -1) {
            fprintf(stderr, "Unknown token '%.*s' at line %zu\n", next.token_len, next.token, lexer.line_no);
            return false;
        }

        BytecodeItem bytecode_item = bytecode_items[bytecode_item_index];
        BytecodeBuffer_push(out_buffer, bytecode_item.value);
        if (bytecode_item.accepts_value) {
            next = Lexer_next_token(&lexer);
            if (!next.token) {
                fprintf(stderr, "Expected operand after %s at line %zu\n", bytecode_item.name, lexer.line_no);
                return false;
            }

            int32_t operand;
            if (!parse_int(next, &operand)) {
                fprintf(stderr, "Could not parse number %.*s at line %zu\n", next.token_len, next.token, lexer.line_no);
                return false;
            }

            BytecodeBuffer_push(out_buffer, (Bytecode) operand);
        }
    }

    return true;
}

int main(int argc, char* args[]) {
    Cli cli = Cli::parse(argc, args);

    BytecodeBuffer buffer = {};
    BytecodeBuffer_init(&buffer, 256);

    if (!compile_input(cli.input.c_str(), &buffer)) {
        fprintf(stderr, "Could not compile input file '%s'\n", cli.input.c_str());
        return EXIT_FAILURE;
    }

    FILE* output = fopen(cli.output.c_str(), "wb");
    if (!output) {
        fprintf(stderr, "Could not open %s for writing\n", cli.output.c_str());
        return EXIT_FAILURE;
    }

    if (fwrite(buffer.buf, sizeof(Bytecode), buffer.len - 1, output) != buffer.len - 1) {
        fprintf(stderr, "Could not write bytecode to file\n");
        return EXIT_FAILURE;
    }

    fclose(output);
    return EXIT_SUCCESS;
}
