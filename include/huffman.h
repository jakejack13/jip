/** huffman.h
 * Tree structure used in implementing Huffman encoding
 */

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdlib.h>
#include <stdio.h>

#include "bitfile.h"

typedef struct huffman_node huffman_t;

struct huffman_node {
    int c;
    int frequency;
    struct huffman_node *left;
    struct huffman_node *right;
    unsigned int code;
    int length;
};

/** Initializes a Huffman tree node */
huffman_t *huffman_init(int c, int frequency);

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
unsigned int huffman_get_code(huffman_t *h, int c);

/** Returns the length of the Huffman code for the character */
int huffman_get_code_length(huffman_t *h, int c);

/** Loads a Huffman tree from the specified file */
huffman_t *huffman_load_from_file(BITFILE *input);

/** Saves the given Huffman tree to the specified file */
void huffman_save_to_file(huffman_t *h, BITFILE *output);

/** Assigns Huffman codes to the nodes in the tree */
void huffman_assign_codes(huffman_t *h);

#endif //HUFFMAN_H
