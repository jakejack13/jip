#include "huffman.h"

huffman_t *huffman_init(int c, int frequency) {
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

static void huffman_assign_codes_recursive(huffman_t *h, unsigned int code, int length) {
    if (h == NULL) return;

    if (h->left == NULL && h->right == NULL) {
        h->code = code;
        h->length = length;
        return;
    }

    huffman_assign_codes_recursive(h->left, code << 1, length + 1);
    huffman_assign_codes_recursive(h->right, (code << 1) | 1, length + 1);
}

unsigned int huffman_get_code(struct huffman_node *h, int c) {
    if (h == NULL) return -1;
    if (h->left == NULL && h->right == NULL) {
        if (h->c == c) {
            return h->code;
        }
        return -1;
    }

    unsigned int result = huffman_get_code(h->left, c);
    if (result != -1) {
        return result;
    }

    return huffman_get_code(h->right, c);
}

int huffman_get_code_length(huffman_t *h, int c) {
    if (h == NULL) return -1;
    if (h->left == NULL && h->right == NULL) {
        if (h->c == c) {
            return h->length;
        }
        return -1;
    }

    int result = huffman_get_code_length(h->left, c);
    if (result != -1) {
        return result;
    }

    return huffman_get_code_length(h->right, c);
}

huffman_t *huffman_load_from_file(BITFILE *input) {
    int bit = bitfile_getc(input);
    if (bit == EOF) {
        return NULL;
    }
    if (bit == 1) {
        // This is a leaf node
        int is_eof_char = bitfile_getc(input);
        if (is_eof_char == EOF) return NULL;

        if (is_eof_char == 1) {
            // It's the EOF_CHAR
            return huffman_init(EOF_CHAR, 0);
        } else {
            // It's a regular character
            int c = 0;
            for (int i = 7; i >= 0; i--) { // Read 8 bits for the character
                bit = bitfile_getc(input);
                if (bit == EOF) return NULL; // Handle unexpected EOF
                c = (c << 1) | bit;
            }
            return huffman_init(c, 0);
        }
    } else {
        // This is an internal node
        huffman_t *node = huffman_init(-1, 0);
        node->left = huffman_load_from_file(input);
        if (node->left == NULL) {
            free(node);
            return NULL;
        }
        node->right = huffman_load_from_file(input);
        if (node->right == NULL) {
            huffman_free(node->left);
            free(node);
            return NULL;
        }
        return node;
    }
}

void huffman_assign_codes(huffman_t *h) {
    huffman_assign_codes_recursive(h, 0, 0);
}

void huffman_save_to_file(huffman_t *h, BITFILE *output) {
    if (h->left == NULL && h->right == NULL) {
        bitfile_putc(1, output); // Indicate leaf node
        if (h->c == EOF_CHAR) {
            bitfile_putc(1, output); // Indicate EOF_CHAR
        } else {
            bitfile_putc(0, output); // Indicate regular character
            for (int i = 7; i >= 0; i--) {
            bitfile_putc((h->c >> i) & 1, output);
        }
        }
    } else {
        bitfile_putc(0, output); // Indicate internal node
        huffman_save_to_file(h->left, output);
        huffman_save_to_file(h->right, output);
    }
}

