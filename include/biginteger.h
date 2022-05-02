/** biginteger.h
 * Big integer data structure used to store large Huffman codes
 */

#ifndef BIGINTEGER_H
#define BIGINTEGER_H

/** The two bits that can be added to big integers */
enum bit {
    ZERO=0,
    ONE=1
};

/** The data structure for big integers */
struct biginteger {
    enum bit *bits;
    unsigned int size;
    unsigned int used;
};

/** Intitializes the big integer to value 0 with the specified size in 
 * bits */
void biginteger_init(struct biginteger *i, unsigned int size);

/** Frees the big integer in memory */
void biginteger_free(struct biginteger *i);

/** Adds the specified bit to the big integer */
void biginteger_add(struct biginteger *i, enum bit n);

/** Left shifts the specified bit into the big integer */
void biginteger_left_shift(struct biginteger *i, enum bit n);

/** Returns the zero-indexed least to most significant specified bit
 * of the big integer */
enum bit biginteger_get_bit(struct biginteger *i, unsigned int bit);

/** Returns the size of the big integer in bits */
unsigned int biginteger_get_size(struct biginteger *i);

#endif //BIGINTEGER_H
