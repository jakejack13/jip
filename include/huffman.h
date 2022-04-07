#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdlib.h>

struct huffman_node {
    char c;
    int frequency;
    struct huffman_node *left;
    struct huffman_node *right;
};

/** Initializes a Huffman tree node */
void huffman_init(struct huffman_node *h, char c, int frequency);

/** Frees a Huffman tree node in memory */
void huffman_free(struct huffman_node *h);

/** Adds a new left Huffman node to the root node */
void huffman_add_left(struct huffman_node *root, struct huffman_node *left);

/** Adds a new right Huffman node to the root node */
void huffman_add_right(struct huffman_node *root, struct huffman_node *right);

/** Returns the Huffman code for the character */
int huffman_get_code(struct huffman_node *h, char c);
#endif //HUFFMAN_H