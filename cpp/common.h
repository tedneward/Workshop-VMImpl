//
// Created by George Liontos on 19/4/24.
//

#ifndef CPP_COMMON_H
#define CPP_COMMON_H

#include <stdlib.h>
#include <stdint.h>

#define internal static

#define MALLOC(size, type) ((type*) malloc((size) * sizeof(type)))

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define ABS(x) ((x) > 0 ? (x) : -(x))

inline int number_of_digits(int n) {
    if (n == 0) {
        return 1;
    }

    int count = 0;
    while (n != 0) {
        n /= 10;
        ++count;
    }

    return count;
}

#endif //CPP_COMMON_H
