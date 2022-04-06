#ifndef TEST_COUNTER_C
#define TEST_COUNTER_C
#include <stdlib.h>
#include <stdio.h>
#include "utils.c"

#include "counter.h"


static int ran = 0;
static int passed = 0;

static void test_add_one_char() {
    struct counter *c = malloc(sizeof(struct counter *));
    counter_init(c);
    counter_add(c, 'a');
    unsigned int result = counter_get(c, 'a');
    if (result != 1) {
        printf("test_counter, test_add_one_char, counter_get expected %u but got %u\n", 1, result);
        passed--;
    }
    ran++;
    passed++;
    result = counter_get(c, 'b');
    if (result != 0) {
        printf("test_counter, test_add_one_char, counter_get expected %u but got %u\n", 0, result);
        passed--;
    }
    ran++;
    passed++;
    counter_free(c);
    free(c);
}


void test_counter_main(struct testresults *results) {
    test_add_one_char();
    results->num_passed = passed;
    results->num_ran = ran;
}

#endif //TEST_COUNTER_C