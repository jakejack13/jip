#include <stdbool.h>

#include "counter.h"


struct counter {
    unsigned int counts[NUMCHARS];
};


// Kept for backwards compatibility
void counter_init(struct counter *c) {
    return;
}

// Kept for backwards compatibility
void counter_free(struct counter *c) {
    return;
}

void counter_add(struct counter *c, char ch) {
    c->counts[(int) ch]++;
}

unsigned int counter_get(struct counter *c, char ch) {
    return c->counts[(int) ch];
}

/** Checks if char xh is in array arr up to a given bound */
static bool is_in(char *arr, char ch, int bound) {
    for (int i = 0; i < bound; i++) {
        if (arr[i] == ch) return true;
    }
    return false;
}

void counter_rank(struct counter *c, char *arr) {
    for (int i = 0; i < NUMCHARS; i++) {
        char max_char;
        unsigned int max_val; 
        for (int j = 0; j < NUMCHARS; j++) {
            if (c->counts[j] > max_val && !is_in(arr, j, i)) {
                max_char = j;
                max_val = c->counts[j];
            }
        }
        arr[i] = max_char;
    }
}
