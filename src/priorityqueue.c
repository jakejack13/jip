#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "priorityqueue.h"

#define INITCAP 10

/* Util macros */
#define LEFT(x) (2 * (x) + 1)
#define RIGHT(x) (2 * (x) + 2)
#define PARENT(x) ((x) / 2)


struct node {
    void *elm;
    int priority;
};

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
    void *tmp = NULL;
    int l_idx, r_idx, lrg_idx;

    l_idx = LEFT(i);
    r_idx = RIGHT(i);

    if (l_idx < pq->size && compare(pq->queue[l_idx], pq->queue[i]) > 0) {
        lrg_idx = l_idx;
    } else {
        lrg_idx = i;
    }

    if (r_idx < pq->size && compare(pq->queue[r_idx], pq->queue[lrg_idx]) > 0) {
        lrg_idx = r_idx;
    }

    if (lrg_idx != i) {
        tmp = pq->queue[lrg_idx];
        pq->queue[lrg_idx] = pq->queue[i];
        pq->queue[i] = tmp;
        heapify(pq, lrg_idx);
    }
}

void priorityqueue_init(struct priorityqueue *pq) {
    pq->queue = malloc(sizeof(struct node *) * INITCAP);
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
    pq->queue[pq->size] = newelm;
    
    int i = pq->size;
    pq->size++;
    void *tmp = NULL;
    while(i > 0 && compare(pq->queue[i], pq->queue[PARENT(i)]) > 0) {
        tmp = pq->queue[i];
        pq->queue[i] = pq->queue[PARENT(i)];
        pq->queue[PARENT(i)] = tmp;
        i = PARENT(i);
    }
}

void *priorityqueue_get(struct priorityqueue *pq) {
    if (pq->size < 1) return NULL;
    struct node *result = pq->queue[0];
    pq->queue[0] = pq->queue[pq->size-1];
    pq->size--;
    heapify(pq, 0);
    void *elm = result->elm;
    free(result);
    return elm;
}

void *priorityqueue_peek(struct priorityqueue *pq) {
    return pq->queue[0];
}

int priorityqueue_length(struct priorityqueue *pq) {
    return pq->size;
}

#ifdef DEBUG
void print_queue(struct priorityqueue *pq) {
    for (int i = 0; i < pq->size; i++) {
        printf("(%p, %d)", pq->queue[i]->elm, pq->queue[i]->priority);
    }
}
#endif
