//
// Created by George Liontos on 20/4/24.
//

#ifndef COMPILER_COMMON_H
#define COMPILER_COMMON_H

#include <stdlib.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#define MALLOC(size, type) ((type*) malloc((size) * sizeof(type)))

#endif //COMPILER_COMMON_H
