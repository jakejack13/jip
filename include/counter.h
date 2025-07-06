/** counter.h
 * Counting data structure used to count characters found in files.
 * Implemented using hash tables, used for Huffman encoding.
 */

#ifndef COUNTER_H
#define COUNTER_H

/** The number of characters */
#define NUMCHARS 257
#define EOF_CHAR 256

/** The data structure for counting characters */
struct counter {
    unsigned int *counts;
};

/** Intitializes the counter */
void counter_init(struct counter *c);

/** Frees the counter in memory */
void counter_free(struct counter *c);

/** Adds a character to the counter */
void counter_add(struct counter *c, int ch);

/** Returns the number of times a character has been added to the counter */
unsigned int counter_get(struct counter *c, int ch);

/** Fills the given array with the counts of each characterm with the index
 * corresponding to the character */
void counter_fill(struct counter *c, int *arr);

#endif  // COUNTER_H