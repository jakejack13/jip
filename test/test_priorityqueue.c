#ifndef TEST_PRIORITYQUEUE_C
#define TEST_PRIORITYQUEUE_C
#include <stdlib.h>
#include <stdio.h>
#include "utils.c"

#include "priorityqueue.h"


static void priorityqueue_test_add_one_char(struct testresults *results) {
    struct priorityqueue *pq = malloc(sizeof(struct priorityqueue));
    priorityqueue_init(pq);
    char a = 'a';
    priorityqueue_add(pq, &a, 1);
    char *result = priorityqueue_get(pq);
    #pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
    assert((int) &a, (int) result, "test_priorityqueue, priorityqueue_test_add_one_char, priorityqueue_get", results);
    result = priorityqueue_get(pq);
    #pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
    assert(0, (int) result, "test_priorityqueue, priorityqueue_test_add_one_char, priorityqueue_get", results);
    priorityqueue_free(pq);
    free(pq);
}

static void priorityqueue_test_add_many_int_forward(struct testresults *results) {
    #define SIZE 100
    struct priorityqueue *pq = malloc(sizeof(struct priorityqueue));
    priorityqueue_init(pq);
    int arr[SIZE];
    for (int i = 0; i < SIZE; i++) arr[i] = i;
    for (int i = 0; i < SIZE; i++) priorityqueue_add(pq, arr+i, i);
    for (int i = 0; i < SIZE; i++) assert((int) i, (int) *((int *)priorityqueue_get(pq)), "test_priorityqueue, priorityqueue_test_add_many_int, priorityqueue_get", results);
    priorityqueue_free(pq);
    free(pq);
}

static void priorityqueue_test_add_many_int_backward(struct testresults *results) {
    #define SIZE 100
    struct priorityqueue *pq = malloc(sizeof(struct priorityqueue));
    priorityqueue_init(pq);
    int arr[SIZE];
    for (int i = 0; i < SIZE; i++) arr[i] = i;
    for (int i = SIZE-1; i >= 0; i--) priorityqueue_add(pq, arr+i, i);
    for (int i = 0; i < SIZE; i++) assert((int) i, (int) *((int *)priorityqueue_get(pq)), "test_priorityqueue, priorityqueue_test_add_many_int, priorityqueue_get", results);
    priorityqueue_free(pq);
    free(pq);
}


void test_priorityqueue_main(struct testresults *results) {
    priorityqueue_test_add_one_char(results);
    priorityqueue_test_add_many_int_forward(results);
    priorityqueue_test_add_many_int_backward(results);
}

#endif //TEST_PRIORITYQUEUE_C