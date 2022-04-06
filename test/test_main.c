#include <stdio.h>

#include "test_counter.c"
#include "utils.c"

int main() {
    int ran = 0;
    int passed = 0;
    printf("Begin tests\n");
    struct testresults test_counter_res;
    test_counter_main(&test_counter_res);
    ran+=test_counter_res.num_ran;
    passed+=test_counter_res.num_passed;
    printf("End tests\n");
    printf("Passed: %d, Ran: %d\n", passed, ran);
}
