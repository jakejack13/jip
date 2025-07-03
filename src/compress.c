#include <math.h>

#include "counter.h"
#include "priorityqueue.h"
#include "huffman.h"

#include "compress.h"

void compress(FILE *input, BITFILE *output) {
    struct counter c;
    counter_init(&c);
    char next = 'a';
    for (;;) {
        next = fgetc(input);
        if (next == EOF) break;
        counter_add(&c, next);
    }
    int arr[NUMCHARS];
    counter_fill(&c, arr);
    
    struct priorityqueue pq;
    priorityqueue_init(&pq);
    for (int i = 0; i < NUMCHARS; i++) {
        huffman_t *node = huffman_init((char) i, arr[i]);
        priorityqueue_add(&pq, node, arr[i]);
    }

    while (priorityqueue_length(&pq) > 1) {
        huffman_t *left = priorityqueue_get(&pq);
        huffman_t *right = priorityqueue_get(&pq);
        int new_frequency = huffman_get_frequency(left) + huffman_get_frequency(right);
        huffman_t *internal = huffman_init(-1, new_frequency);
        huffman_add_left(internal, left);
        huffman_add_right(internal, right);
        priorityqueue_add(&pq, internal, new_frequency);
    }
    huffman_t *root = priorityqueue_get(&pq);

    rewind(input);
    huffman_save_to_file(root, output);
    next = 'a';
    for (;;) {
        next = fgetc(input);
        if (next == EOF) break;
        int code = huffman_get_code(root, next);
        int length = (int) log2(huffman_get_code(root, next)) + 1;
        for (int i = length - 1; i >= 0; i--) {
            bitfile_putc((code >> i) & 1, output);
        }
    }
    bitfile_sync(output);

    counter_free(&c);
    priorityqueue_free(&pq);
    huffman_free(root);
}

void decompress(BITFILE *input, FILE *output) {

}
