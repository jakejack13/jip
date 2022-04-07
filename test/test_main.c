#include <stdio.h>

#include "test_counter.c"
#include "test_priorityqueue.c"
#include "utils.c"

static struct testresults results;

int main() {
    printf("Begin tests\n");
    test_counter_main(&results);
    test_priorityqueue_main(&results);
    printf("End tests\n");
    printf("Passed: %d, Ran: %d\n", results.num_passed, results.num_ran);
}
