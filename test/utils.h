#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

struct testresults {
    int num_ran;
    int num_passed;
};

extern struct testresults results;

#define assert_true(expression, message) \
    do { \
        results.num_ran++; \
        if (expression) { \
            results.num_passed++; \
        } else { \
            printf("FAIL: %s - %s\n", message, #expression); \
            fflush(stdout); \
        } \
    } while (0)

#define assert_equals_int(expected, actual, message) \
    do { \
        results.num_ran++; \
        if ((expected) == (actual)) { \
            results.num_passed++; \
        } else { \
            printf("FAIL: %s - Expected %d, got %d\n", message, (int)(expected), (int)(actual)); \
            fflush(stdout); \
        } \
    } while (0)

#define assert_not_null(pointer, message) \
    do { \
        results.num_ran++; \
        if ((pointer) != NULL) { \
            results.num_passed++; \
        } else { \
            printf("FAIL: %s - Expected not NULL\n", message); \
            fflush(stdout); \
        } \
    } while (0)

#endif // UTILS_H