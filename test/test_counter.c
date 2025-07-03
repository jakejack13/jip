#include "utils.h"

#include "counter.h"


static void counter_test_add_one_char() {
    struct counter c;
    counter_init(&c);
    counter_add(&c, 'a');
    unsigned int result = counter_get(&c, 'a');
    assert_equals_int(1, result, "test_counter, test_add_one_char, counter_get");
    result = counter_get(&c, 'b');
    assert_equals_int(0, result, "test_counter, test_add_one_char, counter_get");
    counter_free(&c);
}


void test_counter() {
    counter_test_add_one_char();
}
