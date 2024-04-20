//
// Created by George Liontos on 20/4/24.
//

#ifndef CPP_UNIT_TEST_H
#define CPP_UNIT_TEST_H

#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include <stddef.h>
#include <stdio.h>
#include "../common.h"

#define XCONCAT(lhs, rhs) lhs##rhs
#define CONCAT(lhs, rhs) XCONCAT(lhs, rhs)

#define XSTRINGIFY(s) #s
#define STRINGIFY(s) XSTRINGIFY(s)

/* FOREGROUND */
#define RST "\x1B[0m"
#define KBOLD "\x1B[1m"
#define KUNDL "\x1B[4m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST
#define FYEL(x) KYEL x RST
#define FBLU(x) KBLU x RST
#define FMAG(x) KMAG x RST
#define FCYN(x) KCYN x RST
#define FWHT(x) KWHT x RST

#define BOLD(x) KBOLD x RST
#define UNDL(x) KUNDL x RST

#ifdef _WIN32
#define NULL_DEV "NUL:"
#else
#define NULL_DEV "/dev/null"
#endif

#define REPORT_ASSERTION_FAILED(cond)                                          \
  do {                                                                         \
    fprintf(                                                                   \
        stderr,                                                                \
        BOLD(FRED("[TEST] `%s` failed")) "\nAssertion failed in file `%s`, "   \
                                         "line `%d`. Condition: `%s`\n",       \
        __func__, __FILE__, __LINE__, STRINGIFY(cond));                        \
  } while (0)

#define TEST_PASSED()                                                          \
  do {                                                                         \
    fprintf(stderr, BOLD(FGRN("[TEST] `%s` passed successfully")) "\n",        \
            __func__);                                                         \
    return;                                                                    \
  } while (0)

#define ASSERT(cond)                                                           \
  do {                                                                         \
    if (!(cond)) {                                                             \
      REPORT_ASSERTION_FAILED(cond);                                           \
      return;                                                                  \
    }                                                                          \
  } while (0)

#define UNIT_TEST(name) void test_##name()

using TestFn = void (*)();

inline void run_tests(TestFn tests[], size_t num_tests) {
    freopen(NULL_DEV, "w", stdout);
    for (size_t i = 0U; i != num_tests; ++i) {
        tests[i]();
    }
}

#endif

#endif //CPP_UNIT_TEST_H
