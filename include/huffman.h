/** huffman.h
 * Tree structure used in implementing Huffman encoding
 */

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdlib.h>
#include <stdio.h>

#include "bitfile.h"

typedef struct huffman_node huffman_t;

/** Initializes a Huffman tree node */
huffman_t *huffman_init(char c, int frequency);

/** Frees a Huffman tree node in memory */
void huffman_free(huffman_t *h);

/** Adds a new left Huffman node to the root node */
void huffman_add_left(huffman_t *root, huffman_t *left);

/** Adds a new right Huffman node to the root node */
void huffman_add_right(huffman_t *root, huffman_t *right);

/** Returns the frequency of the character represented by the given
 * Huffman node */
int huffman_get_frequency(huffman_t *h);

/** Returns the Huffman code for the character */
unsigned int huffman_get_code(huffman_t *h, char c);

/** Loads a Huffman tree from the specified file */
void huffman_load_from_file(huffman_t *h, FILE *input);

/** Saves the given Huffman tree to the specified file */
void huffman_save_to_file(huffman_t *h, FILE *output);

#endif //HUFFMAN_H
