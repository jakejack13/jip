#include "huffman.h"

void huffman_init(struct huffman_node *h, char c, int frequency) {
    h->c = c;
    h->frequency = frequency;
    h->left = NULL;
    h->right = NULL;
}

void huffman_free(struct huffman_node *h) {
    if (h == NULL) return;
    huffman_free(h->left);
    huffman_free(h->right);
    free(h);
}

void huffman_add_left(struct huffman_node *root, struct huffman_node *left) {
    root->left = left;
}

void huffman_add_right(struct huffman_node *root, struct huffman_node *right) {
    root->right = right;
}

int huffman_get_frequency(struct huffman_node *h) {
    if (h == NULL) return 0;
    return h->frequency;
}

int huffman_get_code(struct huffman_node *h, char c) {
    if (h == NULL) return -1;
    else if (h->left == NULL && h->right == NULL) {
        if (h->c == c) return 0;
        return -1;
    }
    int result = huffman_get_code(h->left, c);
    if (result != -1) return result << 1;
    result = huffman_get_code(h->right, c);
    if (result != -1) return (result << 1) + 1;
    return -1;
}
