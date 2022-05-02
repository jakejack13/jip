/** huffman.h
 * Tree structure used in implementing Huffman encoding
 */

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdlib.h>

typedef struct huffman_node huffman_t;

/** Initializes a Huffman tree node */
huffman_t *huffman_init(char c, int frequency);

/** Frees a Huffman tree node in memory */
void huffman_free(huffman_t *h);

/** Adds a new left Huffman node to the root node */
void huffman_add_left(huffman_t *root, huffman_t *left);

/** Adds a new right Huffman node to the root node */
void huffman_add_right(huffman_t *root, huffman_t *right);

int huffman_get_frequency(huffman_t *h);

/** Returns the Huffman code for the character */
int huffman_get_code(huffman_t *h, char c);
#endif //HUFFMAN_H