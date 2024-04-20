//
// Created by George Liontos on 19/4/24.
//

#ifndef CPP_FORMAT_BUFFER_H
#define CPP_FORMAT_BUFFER_H

struct FormatBuffer {
    char* buf;
    size_t len;
    size_t capacity;
};

void FormatBuffer_init(FormatBuffer* buf, size_t capacity);
void FormatBuffer_free(FormatBuffer* buf);
void FormatBuffer_push_str(FormatBuffer* buf, const char* str);
void FormatBuffer_push_number(FormatBuffer* buf, int n);
void FormatBuffer_clear(FormatBuffer* buf);

void format_number_array(int* arr, size_t arr_size, FormatBuffer* fmt_buf);
FormatBuffer allocate_and_format_number_array(int* arr, size_t arr_size);

#endif //CPP_FORMAT_BUFFER_H
