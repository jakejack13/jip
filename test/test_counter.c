#ifndef TEST_COUNTER_C
#define TEST_COUNTER_C
#include <stdlib.h>
#include <stdio.h>
#include "utils.c"

#include "counter.h"


static void counter_test_add_one_char(struct testresults *results) {
    struct counter *c = malloc(sizeof(struct counter *));
    counter_init(c);
    counter_add(c, 'a');
    unsigned int result = counter_get(c, 'a');
    assert(1, result, "test_counter, test_add_one_char, counter_get", results);
    result = counter_get(c, 'b');
    assert(0, result, "test_counter, test_add_one_char, counter_get", results);
    counter_free(c);
    free(c);
}

static void counter_test_one_rank(struct testresults *results) {
    struct counter *c = malloc(sizeof(struct counter *));
    counter_init(c);
    counter_add(c, 'a');
    char *arr = malloc(sizeof(char) * NUMCHARS);
    counter_rank(c, arr);
    assert('a', arr[0], "test_counter, test_one_rank, counter_rank", results);
    free(arr);
}


void test_counter_main(struct testresults *results) {
    counter_test_add_one_char(results);
    counter_test_one_rank(results);
}

#endif //TEST_COUNTER_C