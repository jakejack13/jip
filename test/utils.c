#ifndef UTILS_C
#define UTILS_C

struct testresults {
    int num_ran;
    int num_passed;
};

void assert(int expected, int actual, const char *message, struct testresults *results) {
    if (expected != actual) {
        printf("%s: expected %d but was actually %d\n", message, expected, actual);
        results->num_passed--;
    }
    results->num_ran++;
    results->num_passed++;
}

#endif //UTILS_C