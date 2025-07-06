#include "counter.h"

#include <stdbool.h>
#include <stdlib.h>

void counter_init(struct counter *c) {
    c->counts = malloc(sizeof(int) * NUMCHARS);
    for (int i = 0; i < NUMCHARS; i++) c->counts[i] = 0;
}

void counter_free(struct counter *c) { free(c->counts); }

void counter_add(struct counter *c, int ch) { c->counts[ch]++; }

unsigned int counter_get(struct counter *c, int ch) {
    return c->counts[(int)ch];
}

void counter_fill(struct counter *c, int *arr) {
    for (int i = 0; i < NUMCHARS; i++) {
        arr[i] = c->counts[i];
    }
}
