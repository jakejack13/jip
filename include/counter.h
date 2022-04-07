#ifndef COUNTER_H
#define COUNTER_H

/** The number of characters */
#define NUMCHARS 256

/** The data structure for counting characters */
struct counter;

/** Intitializes the counter */
void counter_init(struct counter *c);

/** Frees the counter in memory */
void counter_free(struct counter *c);

/** Adds a character to the counter */
void counter_add(struct counter *c, char ch);

/** Returns the number of times a character has been added to the counter */
unsigned int counter_get(struct counter *c, char ch);

/** Fills the given array with all characters in order or most frequent to least frequent */
void counter_rank(struct counter *c, char *arr);

#endif //COUNTER_H