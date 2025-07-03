#include "huffman.h"

struct huffman_node {
    char c;
    int frequency;
    struct huffman_node *left;
    struct huffman_node *right;
};

huffman_t *huffman_init(char c, int frequency) {
    huffman_t *h = malloc(sizeof(struct huffman_node));
    h->c = c;
    h->frequency = frequency;
    h->left = NULL;
    h->right = NULL;
    return h;
}

void huffman_free(huffman_t *h) {
    if (h == NULL) return;
    huffman_free(h->left);
    huffman_free(h->right);
    free(h);
}

void huffman_add_left(huffman_t *root, huffman_t *left) {
    if (root->left != NULL) return;
    root->left = left;
}

void huffman_add_right(huffman_t *root, huffman_t *right) {
    if (root->right != NULL) return;
    root->right = right;
}

int huffman_get_frequency(huffman_t *h) {
    if (h == NULL) return 0;
    return h->frequency;
}

static unsigned int huffman_get_code_helper(struct huffman_node *h, char c, unsigned int code, int depth) {
    if (h == NULL) return -1;
    if (h->left == NULL && h->right == NULL) {
        if (h->c == c) {
            return code;
        }
        return -1;
    }

    unsigned int result = huffman_get_code_helper(h->left, c, code, depth + 1);
    if (result != -1) {
        return result;
    }

    code |= (1 << depth);
    return huffman_get_code_helper(h->right, c, code, depth + 1);
}

unsigned int huffman_get_code(struct huffman_node *h, char c) {
    return huffman_get_code_helper(h, c, 0, 0);
}

void huffman_load_from_file(huffman_t *h, BITFILE *input) {
    #warning "TODO"
}

void huffman_save_to_file(huffman_t *h, BITFILE *output) {
    #warning "TODO"
}
