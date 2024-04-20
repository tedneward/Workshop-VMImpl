//
// Created by George Liontos on 20/4/24.
//

#include "cli.h"
#include "virtual_machine.h"
#include "common.h"
#include "entire_file.h"


internal bool read_bytecode(const char* path, Bytecode** bytecode_out, size_t* num_codes) {
    EntireFile file = read_entire_file_into_memory(path);
    if (!file.contents) {
        return false;
    }

    *bytecode_out = (Bytecode*) file.contents;
    *num_codes = file.num_bytes / sizeof(Bytecode);
    return true;
}

int main(int argc, char* args[]) {
    Cli cli = Cli::parse(argc, args);

    Bytecode* codes = nullptr;
    size_t num_codes = 0;
    if (!read_bytecode(cli.input.c_str(), &codes, &num_codes)) {
        fprintf(stderr, "Failed to read bytecode from file '%s'\n", cli.input.c_str());
        return EXIT_FAILURE;
    }

    VirtualMachine vm = {};
    vm.trace = cli.trace;

    vm_execute(&vm, codes, num_codes);

    free(codes);

    return EXIT_SUCCESS;
}
