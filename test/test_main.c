#include <stdio.h>

#include "test_counter.c"
#include "utils.c"

static struct testresults results;

int main() {
    printf("Begin tests\n");
    test_counter_main(&results);
    printf("End tests\n");
    printf("Passed: %d, Ran: %d\n", results.num_passed, results.num_ran);
}
