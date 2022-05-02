#ifndef TEST_BIGINTEGER_C
#define TEST_BIGINTEGER_C
#include "utils.c"

#include "biginteger.h"

static void biginteger_test_zero(struct testresults *results) {
    struct biginteger i;
    biginteger_init(&i, 1);
    biginteger_add(&i, ZERO);

    enum bit result = biginteger_get_bit(&i, 0);
    assert(ZERO, result, "test_biginteger, biginteger_test_add_zero, biginteger_get_bit 0", results);

    biginteger_free(&i);
}

static void biginteger_test_one(struct testresults *results) {
    struct biginteger i;
    biginteger_init(&i, 1);
    biginteger_add(&i, ONE);

    enum bit result = biginteger_get_bit(&i, 0);
    assert(ONE, result, "test_biginteger, biginteger_test_add_one, biginteger_get_bit 0", results);

    biginteger_free(&i);
}

static void biginteger_test_two(struct testresults *results) {
    struct biginteger i;
    biginteger_init(&i, 2);
    biginteger_add(&i, ONE);
    biginteger_add(&i, ONE);

    enum bit result = biginteger_get_bit(&i, 0);
    assert(ZERO, result, "test_biginteger, biginteger_test_add_two, biginteger_get_bit 0", results);
    result = biginteger_get_bit(&i, 1);
    assert(ONE, result, "test_biginteger, biginteger_test_add_two, biginteger_get_bit 1", results);

    biginteger_free(&i);
}

static void biginteger_test_three(struct testresults *results) {
    struct biginteger i;
    biginteger_init(&i, 2);
    biginteger_add(&i, ONE);
    biginteger_add(&i, ONE);
    biginteger_add(&i, ONE);

    enum bit result = biginteger_get_bit(&i, 0);
    assert(ONE, result, "test_biginteger, biginteger_test_add_three, biginteger_get_bit 0", results);
    result = biginteger_get_bit(&i, 1);
    assert(ONE, result, "test_biginteger, biginteger_test_add_three, biginteger_get_bit 1", results);

    biginteger_free(&i);
}

void test_biginteger_main(struct testresults *results) {
    biginteger_test_zero(results);
    biginteger_test_one(results);
    biginteger_test_two(results);
    biginteger_test_three(results);
}

#endif //TEST_BIGINTEGER_C