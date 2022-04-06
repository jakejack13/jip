/** The data structure for counting characters */
struct counter;

/** Intitializes a counter */
void counter_init(struct counter *c);

/** Frees a counter in memory */
void counter_free(struct counter *c);

/** Adds a character to the counter */
void counter_add(struct counter *c, char ch);

/** Gets the number of times a character has been added to the counter */
unsigned int counter_get(struct counter *c, char ch);

/** Gets the character at the specified 0-indexed rank, where lower rank means higher frequency */
char counter_rank(struct counter *c, unsigned int r);
