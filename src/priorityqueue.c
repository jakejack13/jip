#include <stdlib.h>
#include <string.h>

#include "priorityqueue.h"

#define INITCAP 10

struct node {
    void *elm;
    int priority;
};

/** Swaps the memory locations */
static void swap(struct node **a, struct node **b) {
  struct node *temp = *b;
  *b = *a;
  *a = temp;
}

/** Returns 1 if the first argument is higher priority than the second 
 * argument and 0 otherwise */
static bool compare(struct node *a, struct node *b) {
    if (a == NULL) return false;
    else if (b == NULL) return true;
    return a->priority < b->priority;
}

/** Clears the memory allocated for the queue to prevent dirty memory issues */
static void clear_queue(struct priorityqueue *pq, int begin, int end) {
    memset(pq->queue+begin, 0, sizeof(void *) * (end-begin));
}

/** Doubles the capacity of the priority queue */
static void resize(struct priorityqueue *pq) {
    pq->capacity*=2;
    pq->queue = realloc(pq->queue, sizeof(struct node *) * pq->capacity);
    clear_queue(pq, pq->size, pq->capacity);
}

/** Fixes the heap invariant of the priority queue */
static void heapify(struct priorityqueue *pq, int i) {
    if (pq->size <= 1) return;
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < pq->size && compare(pq->queue[l], pq->queue[largest])) largest = l;
    if (r < pq->size && compare(pq->queue[r], pq->queue[largest])) largest = r;

    // Swap and continue heapifying if root is not largest
    if (largest != i) {
        swap(&pq->queue[i], &pq->queue[largest]);
        heapify(pq, largest);
    }
}

void priorityqueue_init(struct priorityqueue *pq) {
    pq->queue = malloc(sizeof(void *) * INITCAP);
    pq->size = 0;
    pq->capacity = INITCAP;
    clear_queue(pq, pq->size, pq->capacity - pq->size);
}

void priorityqueue_free(struct priorityqueue *pq) {
    for (int i = 0; i < pq->size; i++) {
        free(pq->queue[i]);
    }
    free(pq->queue);
}

void priorityqueue_add(struct priorityqueue *pq, void *elm, int priority) {
    if (pq->size == pq->capacity) resize(pq);
    struct node *newelm = malloc(sizeof(struct node));
    newelm->elm = elm;
    newelm->priority = priority;
    pq->queue[pq->size++] = newelm;
    for (int i = pq->size / 2 - 1; i >= 0; i--) {
      heapify(pq, i);
    }
}

void *priorityqueue_get(struct priorityqueue *pq) {
    struct node *result = pq->queue[0];
    pq->queue[0] = NULL;
    for (int i = pq->size / 2 - 1; i >= 0; i--) {
        heapify(pq, i);
    }
    if (result == NULL) return NULL;
    void *elm = result->elm;
    free(result);
    return elm;
}

void *priorityqueue_peek(struct priorityqueue *pq) {
    return pq->queue[0];
}
