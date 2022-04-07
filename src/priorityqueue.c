#include <stdlib.h>
#include <string.h>

#include "priorityqueue.h"

#define INITCAP 10

struct priorityqueue {
    void **queue;
    int size;
    int capacity;
    compare_t f;
};

/** Swaps the memory locations */
static void swap(int *a, int *b) {
  int temp = *b;
  *b = *a;
  *a = temp;
}

/** Clears the memory allocated for the queue to prevent dirty memory issues */
static void clear_queue(struct priorityqueue *pq, int begin, int end) {
    memset(pq->queue+begin, 0, sizeof(void *) * (end-begin));
}

/** Doubles the capacity of the priority queue */
static void resize(struct priorityqueue *pq) {
    pq->capacity*=2;
    realloc(pq->queue, sizeof(void *) * pq->capacity);
    clear_queue(pq, pq->size, pq->capacity);
}

/** Fixes the heap invariant of the priority queue */
static void heapify(struct priorityqueue *pq, int i) {
    if (pq->size <= 1) return;
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < pq->size && pq->f(pq->queue[l], pq->queue[largest])) largest = l;
    if (r < pq->size && pq->f(pq->queue[r], pq->queue[largest])) largest = r;

    // Swap and continue heapifying if root is not largest
    if (largest != i) {
        swap(&pq->queue[i], &pq->queue[largest]);
        heapify(pq, largest);
    }
}

void priorityqueue_init(struct priorityqueue *pq, compare_t f) {
    pq->queue = malloc(sizeof(void *) * INITCAP);
    pq->size = 0;
    pq->capacity = INITCAP;
    pq->f = f;
    clear_queue(pq, pq->size, pq->capacity - pq->size);
}

void priorityqueue_free(struct priorityqueue *pq) {
    free(pq->queue);
}

void priorityqueue_add(struct priorityqueue *pq, void *elm, int priority) {
    if (pq->size == pq->capacity) resize(pq);
    pq->queue[++pq->size] = elm;
    for (int i = pq->size / 2 - 1; i >= 0; i--) {
      heapify(pq, i);
    }
}

void *priorityqueue_get(struct priorityqueue *pq) {
    void *result = pq->queue[0];
    pq->queue[0] = NULL;
    for (int i = pq->size / 2 - 1; i >= 0; i--) {
        heapify(pq, i);
    }
}

void *priorityqueue_peek(struct priorityqueue *pq) {
    return pq->queue[0];
}
