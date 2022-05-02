#include "counter.h"
#include "priorityqueue.h"
#include "huffman.h"

#include "compress.h"

void compress(FILE *input, FILE *output) {
    struct counter *c = malloc(sizeof(struct counter));
    counter_init(c);
    char next = 'a';
    for (;;) {
        next = fgetc(input);
        if (next == EOF) break;
        counter_add(c, next);
    }
    int arr[NUMCHARS];
    counter_fill(c, arr);
    
    struct priorityqueue *pq = malloc(sizeof(struct priorityqueue));
    priorityqueue_init(pq);
    for (int i = 0; i < NUMCHARS; i++) {
        huffman_t *node = huffman_init((char) i, arr[i]);
        priorityqueue_add(pq, node, arr[i]);
    }

    while (priorityqueue_length(pq) > 1) {
        huffman_t *left = priorityqueue_get(pq);
        huffman_t *right = priorityqueue_get(pq);
        int new_frequency = huffman_get_frequency(left) + huffman_get_frequency(right);
        huffman_t *internal = huffman_init(-1, new_frequency);
        priorityqueue_add(pq, internal, new_frequency);
    }
    huffman_t *root = priorityqueue_get(pq);

    rewind(input);
    next = 'a';
    for (;;) {
        next = fgetc(input);
        if (next == EOF) break;
        printf("char: %c, ",next);
        int code = huffman_get_code(root, next);
        printf("code: %d\n", code);
        fputc(code, output);
    }

    counter_free(c);
    free(c);
    priorityqueue_free(pq);
    free(pq);
    huffman_free(root);
}

void decompress(FILE *input, FILE *output) {

}
