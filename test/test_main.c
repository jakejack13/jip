#include <stdio.h>

#include "utils.c"

#include "test_counter.c"
#include "test_priorityqueue.c"


static struct testresults results;

int main() {
    printf("Begin tests\n");

    test_counter_main(&results);
    test_priorityqueue_main(&results);
    

    printf("End tests\n");
    printf("Passed: %d, Ran: %d\n", results.num_passed, results.num_ran);
    if (results.num_passed != results.num_ran) return 1;
    return 0;
}
