//
// Created by George Liontos on 19/4/24.
//

#include "common.h"
#include "format_buffer.h"

#include <assert.h>
#include <string.h>
#include <stdio.h>

void FormatBuffer_init(FormatBuffer* buf, size_t capacity) {
    buf->buf = MALLOC(capacity, char);
    buf->len = 0;
    buf->capacity = capacity;
}

void FormatBuffer_free(FormatBuffer* buf) {
    if (buf->buf) {
        free(buf->buf);
    }
}

internal inline size_t FormatBuffer_available_bytes(FormatBuffer* fmt_buf) {
    return fmt_buf->capacity - fmt_buf->len;
}

internal void FormatBuffer_grow_if_necessary(FormatBuffer* fmt_buf, size_t required_len) {
    if (FormatBuffer_available_bytes(fmt_buf) < required_len + 1) {
        char* new_buf = MALLOC(fmt_buf->capacity + required_len + 1, char);
        memcpy(new_buf, fmt_buf->buf, fmt_buf->len);
        free(fmt_buf->buf);
        fmt_buf->buf = new_buf;
        fmt_buf->capacity += required_len + 1;
    }
}

void FormatBuffer_push_str(FormatBuffer* fmt_buf, const char* str) {
    size_t str_size = strlen(str);
    FormatBuffer_grow_if_necessary(fmt_buf, str_size);

    int bytes_written = snprintf(fmt_buf->buf + fmt_buf->len, FormatBuffer_available_bytes(fmt_buf), "%s", str);

    assert(bytes_written != -1);
    assert(bytes_written == str_size);

    fmt_buf->buf[fmt_buf->len + bytes_written] = 0;
    fmt_buf->len += bytes_written;
}

void FormatBuffer_push_number(FormatBuffer* fmt_buf, int32_t n) {
    int num_digits = number_of_digits(n);
    FormatBuffer_grow_if_necessary(fmt_buf, num_digits);

    int bytes_written = snprintf(fmt_buf->buf + fmt_buf->len, FormatBuffer_available_bytes(fmt_buf), "%d", n);

    assert(bytes_written != -1);
    assert(bytes_written == num_digits);
    fmt_buf->buf[fmt_buf->len + bytes_written] = 0;
    fmt_buf->len += bytes_written;
}

void FormatBuffer_clear(FormatBuffer* fmt_buf) {
    fmt_buf->len = 0;
}


void format_number_array(int32_t* arr, size_t arr_size, FormatBuffer* fmt_buf) {
    if (arr_size == 0) {
        FormatBuffer_push_str(fmt_buf, "[]");
        return;
    }

    for (size_t i = 0U; i != arr_size; ++i) {
        FormatBuffer_push_number(fmt_buf, arr[i]);

        if (i != arr_size - 1) {
            FormatBuffer_push_str(fmt_buf, ", ");
        }
    }
}

FormatBuffer allocate_and_format_number_array(int32_t* arr, size_t arr_size) {
    FormatBuffer res = {0};
    FormatBuffer_init(&res, MAX(arr_size, 3));
    format_number_array(arr, arr_size, &res);
    return res;
}
