#include <stdio.h>

#include "utils.h"

// Declare test functions
void test_counter();
void test_priorityqueue();
void test_huffman();
void test_compress();
void test_bitfile();

struct testresults results;

int main() {
    printf("Begin tests\n");

    test_counter();
    test_priorityqueue();
    test_huffman();
    test_compress();
    // test_bitfile();
    

    printf("End tests\n");
    printf("Passed: %d, Ran: %d\n", results.num_passed, results.num_ran);
    if (results.num_passed != results.num_ran) return 1;
    return 0;
}
