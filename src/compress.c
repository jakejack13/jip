#include "counter.h"
#include "priorityqueue.h"
#include "huffman.h"

#include "compress.h"

void compress(FILE *input, FILE *output) {
    struct counter *c = malloc(sizeof(struct counter));
    counter_init(c);
    char next = 'a';
    while (next != EOF) {
        next = fgetc(input);
        counter_add(c, next);
    }
    int *arr = malloc(sizeof(int) * NUMCHARS);
    counter_fill(c, arr);
    
    struct priorityqueue *pq = malloc(sizeof(struct priorityqueue));
    priorityqueue_init(pq);
    for (int i = 0; i < NUMCHARS; i++) {
        struct huffman_node *node = malloc(sizeof(struct huffman_node));
        huffman_init(node, (char) i, arr[i]);
        priorityqueue_add(pq, node, arr[i]);
    }

    while (priorityqueue_length(pq) > 1) {
        struct huffman_node *left = priorityqueue_get(pq);
        struct huffman_node *right = priorityqueue_get(pq);
        struct huffman_node *internal = malloc(sizeof(struct huffman_node));
        int new_frequency = huffman_get_frequency(left) + huffman_get_frequency(right);
        huffman_init(internal, -1, new_frequency);
        priorityqueue_add(pq, internal, new_frequency);
    }
    struct huffman_node *root = priorityqueue_get(pq);

    rewind(input);
    next = 'a';
    while (next != EOF) {
        next = fgetc(input);
        int code = huffman_get_code(root, next);
        fputc(code, output);
    }

    free(arr);
    counter_free(c);
    free(c);
    priorityqueue_free(pq);
    free(pq);
    huffman_free(root);
}

void decompress(FILE *input, FILE *output) {

}