#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

#include "priorityqueue.h"


#define SIZE 10


static void priorityqueue_test_add_one_char() {
    struct priorityqueue pq;
    priorityqueue_init(&pq);
    char a = 'a';
    priorityqueue_add(&pq, &a, 1);
    char *result = priorityqueue_get(&pq);
    assert_equals_int((int) a, (int) *result, "test_priorityqueue, priorityqueue_test_add_one_char, priorityqueue_get");
    result = priorityqueue_get(&pq);
    assert_true(result == NULL, "test_priorityqueue, priorityqueue_test_add_one_char, priorityqueue_get");
    priorityqueue_free(&pq);
}

static void priorityqueue_test_add_many_int_forward() {
    struct priorityqueue pq;
    priorityqueue_init(&pq);
    int arr[SIZE];
    for (int i = 0; i < SIZE; i++) arr[i] = i;
    for (int i = 0; i < SIZE; i++) priorityqueue_add(&pq, &arr[i], i);
    for (int i = 0; i < SIZE; i++) assert_equals_int(i, *((int *)priorityqueue_get(&pq)), "test_priorityqueue, priorityqueue_test_add_many_int_forward, priorityqueue_get");
    priorityqueue_free(&pq);
}

static void priorityqueue_test_add_many_int_backward() {
    struct priorityqueue pq;
    priorityqueue_init(&pq);
    int arr[SIZE];
    for (int i = 0; i < SIZE; i++) arr[i] = i;
    for (int i = SIZE-1; i >= 0; i--) priorityqueue_add(&pq, &arr[i], i);
    for (int i = 0; i < SIZE; i++) assert_equals_int(i, *((int *)priorityqueue_get(&pq)), "test_priorityqueue, priorityqueue_test_add_many_int_backward, priorityqueue_get");
    priorityqueue_free(&pq);
}


void test_priorityqueue() {
    priorityqueue_test_add_one_char();
    priorityqueue_test_add_many_int_forward();
    priorityqueue_test_add_many_int_backward();
}
