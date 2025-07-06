#include "compress.h"

#include <math.h>
#include <stdio.h>

#include "counter.h"
#include "huffman.h"
#include "priorityqueue.h"

int compress(FILE *input, BITFILE *output) {
    struct counter c;
    counter_init(&c);
    int next_char;
    int is_empty = 1;
    for (;;) {
        next_char = fgetc(input);
        if (next_char == EOF) break;
        is_empty = 0;
        counter_add(&c, next_char);
    }
    if (is_empty) {
        fputc(0, output->below);  // bits_in_last_byte
        fflush(output->below);
        counter_free(&c);
        return 0;
    }

    counter_add(&c, EOF_CHAR);  // Add EOF character

    int arr[NUMCHARS];
    counter_fill(&c, arr);

    struct priorityqueue pq;
    priorityqueue_init(&pq);
    for (int i = 0; i < NUMCHARS; i++) {
        huffman_t *node = huffman_init(i, arr[i]);
        priorityqueue_add(&pq, node, arr[i]);
    }

    while (priorityqueue_length(&pq) > 1) {
        huffman_t *left = priorityqueue_get(&pq);
        huffman_t *right = priorityqueue_get(&pq);
        int new_frequency =
            huffman_get_frequency(left) + huffman_get_frequency(right);
        huffman_t *internal = huffman_init(-1, new_frequency);
        huffman_add_left(internal, left);
        huffman_add_right(internal, right);
        priorityqueue_add(&pq, internal, new_frequency);
    }
    huffman_t *root = priorityqueue_get(&pq);

    huffman_assign_codes(root);  // Assign codes after tree is built

    // Write a placeholder for bits_in_last_byte at the beginning
    fputc(0, output->below);

    rewind(input);
    huffman_save_to_file(root, output);
    for (;;) {
        next_char = fgetc(input);
        if (next_char == EOF) break;
        unsigned int code = huffman_get_code(root, next_char);
        int length = huffman_get_code_length(root, next_char);

        for (int i = length - 1; i >= 0; i--) {
            bitfile_putc((code >> i) & 1, output);
        }
    }
    // Write EOF character code
    unsigned int eof_code = huffman_get_code(root, EOF_CHAR);
    int eof_length = huffman_get_code_length(root, EOF_CHAR);

    for (int i = eof_length - 1; i >= 0; i--) {
        bitfile_putc((eof_code >> i) & 1, output);
    }
    int bits_in_last_byte = bitfile_sync(output);

    // Write the actual bits_in_last_byte to the beginning of the file
    long current_pos = ftell(output->below);
    fseek(output->below, 0, SEEK_SET);
    fputc(bits_in_last_byte, output->below);
    fseek(output->below, current_pos, SEEK_SET);

    counter_free(&c);
    priorityqueue_free(&pq);
    huffman_free(root);
    return bits_in_last_byte;
}

void decompress(BITFILE *input, FILE *output) {
    // Read bits_in_last_byte from the beginning of the file
    int bits_in_last_byte = fgetc(input->below);
    if (bits_in_last_byte == EOF) {
        input->total_bits_to_read = 0;
        return;
    }
    input->bits_in_last_byte = bits_in_last_byte;

    // Recalculate total_bits_to_read after reading bits_in_last_byte
    long current_pos = ftell(input->below);
    fseek(input->below, 0, SEEK_END);
    long file_size = ftell(input->below);
    fseek(input->below, current_pos, SEEK_SET);

    if (file_size > 1) {
        input->total_bits_to_read = (file_size - 1) * 8 + bits_in_last_byte;
    } else if (file_size == 1 && bits_in_last_byte > 0) {
        input->total_bits_to_read = bits_in_last_byte;
    } else {
        input->total_bits_to_read = 0;
    }

    huffman_t *root = huffman_load_from_file(input);
    if (root == NULL) return;  // Handle error during tree loading
    huffman_t *curr = root;
    for (;;) {
        int bit = bitfile_getc(input);
        if (bit == EOF) {
            break;  // Check for EOF from bitfile_getc
        }

        if (bit == 1) {
            curr = curr->right;
        } else {
            curr = curr->left;
        }

        if (curr->left == NULL && curr->right == NULL) {  // Leaf node
            if (curr->c == EOF_CHAR) {
                break;  // Stop before writing EOF_CHAR
            }
            fputc(curr->c, output);
            curr = root;
        }
    }
    huffman_free(root);
}