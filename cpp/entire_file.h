//
// Created by George Liontos on 20/4/24.
//

#ifndef CPP_ENTIRE_FILE_H
#define CPP_ENTIRE_FILE_H

#include <stdio.h>
#include <stddef.h>
#include "common.h"

struct EntireFile {
    char* contents;
    size_t num_bytes;
};

EntireFile read_entire_file_into_memory(const char* path) {
    EntireFile res = {0};
    FILE* f = fopen(path, "rb");
    size_t num_bytes_read = 0U;

    if (f == nullptr) {
        fprintf(stderr, "Could not open '%s' for reading\n", path);
        return res;
    }

    if (fseek(f, 0, SEEK_END) != 0) {
        goto err;
    }

    res.num_bytes = ftell(f);
    if (res.num_bytes == -1L) {
        goto err;
    }

    if (fseek(f, 0, SEEK_SET) != 0) {
        goto err;
    }

    res.contents = MALLOC(res.num_bytes + 1, char);
    num_bytes_read = fread(res.contents, sizeof(char), res.num_bytes, f);
    if (num_bytes_read != res.num_bytes) {
        goto err;
    }

    fclose(f);
    return res;

    err:
    fclose(f);
    if (res.contents) {
        free(res.contents);
    }
    res.contents = nullptr;
    res.num_bytes = 0;
    return res;
}

#endif //CPP_ENTIRE_FILE_H
