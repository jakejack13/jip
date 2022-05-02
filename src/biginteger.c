#include <stdlib.h>

#include "biginteger.h"

void biginteger_init(struct biginteger *i, unsigned int size) {
    i->bits = calloc(size, sizeof(enum bit));
    i->size = size;
    i->used = 0;
}

void biginteger_free(struct biginteger *i) {
    free(i->bits);
}

void biginteger_add(struct biginteger *i, enum bit n) {
    if (n == ZERO) return;
    enum bit carry = n;
    for (int j = i->size-1; j >= i->size-i->used; j--) {
        switch (i->bits[j] + carry) {
            case 0:
            case 1:
                carry = ZERO;
                i->bits[j] = i->bits[j] + carry;
                return;
            case 2:
                carry = ONE;
                i->bits[j] = ZERO;
                break;
        }
    }
    if (carry == ONE && i->used != i->size) {
        i->used++;
        i->bits[i->size-i->used] = carry;
    }
}

void biginteger_left_shift(struct biginteger *i, enum bit n) {
    if (i->used == i->size) return;
    for (int j = i->size-i->used; j < i->size; j++) {
        i->bits[j-1] = i->bits[j];
    }
    i->bits[i->size-1] = n;
    i->used++;
}

enum bit biginteger_get_bit(struct biginteger *i, unsigned int bit) {
    if (bit >= i->size) return ZERO;
    return i->bits[i->size-1-bit];
}

unsigned int biginteger_get_size(struct biginteger *i) {
    return i->used;
}
