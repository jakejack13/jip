#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <stdbool.h>


/** The data structure for the priority queue */
struct priorityqueue;


/** Initializes the priority queue with compare function f */
void priorityqueue_init(struct priorityqueue *pq);

/** Frees the priority queue in memory */
void priorityqueue_free(struct priorityqueue *pq);

/** Adds an element with given priority to the queue (where lower priority level == higher priority) */
void priorityqueue_add(struct priorityqueue *pq, void *elm, int priority);

/** Removes and returns the element with the highest priority */
void *priorityqueue_get(struct priorityqueue *pq);

/** Returns the element with the highest priority */
void *priorityqueue_peek(struct priorityqueue *pq);

#endif //PRIORITYQUEUE_H