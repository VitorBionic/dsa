#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "queues/queue.h"
#include "lists/list.h"

static void build_default_queue(Queue *queue);
static void test_queue_init(void);
static void test_enqueue_one_element(void);
static void test_enqueue_four_elements(void);
static void test_dequeue_one_element(void);
static void test_dequeue_four_elements(void);
static void test_queue_destroy(void);

int main(void) {
    
    test_queue_init();
    test_enqueue_one_element();
    test_enqueue_four_elements();
    test_dequeue_one_element();
    test_dequeue_four_elements();
    test_queue_destroy();
    
    puts("All queue tests passed!");

    return 0;
}

static void test_queue_init(void) {
    Queue queue;

    queue_init(&queue, free);

    assert(queue_size(&queue) == 0);
    assert(queue_peek(&queue) == NULL);

    queue_destroy(&queue);
}

static void test_enqueue_one_element(void) {
    Queue queue;
    int *value;

    value = malloc(sizeof(int));
    assert(value != NULL);
    *value = 42;

    queue_init(&queue, free);

    assert(queue_peek(&queue) == NULL);

    assert(queue_enqueue(&queue, value) == 0);

    assert(queue_size(&queue) == 1);
    assert(*(int *)queue_peek(&queue) == 42);

    queue_destroy(&queue);
}

static void test_enqueue_four_elements(void) {
    Queue queue;
    int *value1, *value2, *value3, *value4;

    value1 = malloc(sizeof(int));
    assert(value1 != NULL);
    *value1 = 42;

    value2 = malloc(sizeof(int));
    assert(value2 != NULL);
    *value2 = 24;

    value3 = malloc(sizeof(int));
    assert(value3 != NULL);
    *value3 = 52;
    
    value4 = malloc(sizeof(int));
    assert(value4 != NULL);
    *value4 = 10;

    queue_init(&queue, free);

    assert(queue_enqueue(&queue, value1) == 0);
    assert(queue_enqueue(&queue, value2) == 0);
    assert(queue_enqueue(&queue, value3) == 0);
    assert(queue_enqueue(&queue, value4) == 0);

    ListElmt *current;

    assert(queue_size(&queue) == 4);
    assert(*(int *)queue_peek(&queue) == 42);

    current = list_head(&queue);

    // 42, 24, 52, 10
    assert(*(int *)list_data(current) == 42);
    current = list_next(current);
    assert(*(int *)list_data(current) == 24);
    current = list_next(current);
    assert(*(int *)list_data(current) == 52);
    current = list_next(current);
    assert(*(int *)list_data(current) == 10);

    queue_destroy(&queue);

}

static void test_dequeue_one_element(void) {
    Queue queue;

    build_default_queue(&queue);
    assert(queue_size(&queue) == 4);
    assert(*(int *)queue_peek(&queue) == 42);

    int *data;

    assert(queue_dequeue(&queue, (void **)&data) == 0);

    assert(*data == 42);
    free(data);

    assert(queue_size(&queue) == 3);
    assert(*(int *)queue_peek(&queue) == 24);

    ListElmt *current;

    current = list_head(&queue);

    assert(*(int *)list_data(current) == 24);
    current = list_next(current);
    assert(*(int *)list_data(current) == 52);
    current = list_next(current);
    assert(*(int *)list_data(current) == 10);

    queue_destroy(&queue);
}

static void test_dequeue_four_elements(void) {
    Queue queue;

    build_default_queue(&queue);

    assert(queue_size(&queue) == 4);
    assert(*(int *)queue_peek(&queue) == 42);

    int *data;

    assert(queue_dequeue(&queue, (void **)&data) == 0);

    assert(*data == 42);
    free(data);

    assert(queue_size(&queue) == 3);
    assert(*(int *)queue_peek(&queue) == 24);

    assert(queue_dequeue(&queue, (void **)&data) == 0);

    assert(*data == 24);
    free(data);

    assert(queue_size(&queue) == 2);
    assert(*(int *)queue_peek(&queue) == 52);

    assert(queue_dequeue(&queue, (void **)&data) == 0);

    assert(*data == 52);
    free(data);

    assert(queue_size(&queue) == 1);
    assert(*(int *)queue_peek(&queue) == 10);

    assert(queue_dequeue(&queue, (void **)&data) == 0);

    assert(*data == 10);
    free(data);

    assert(queue_size(&queue) == 0);
    assert(queue_peek(&queue) == NULL);

    queue_destroy(&queue);
}

static void test_queue_destroy(void) {
    Queue queue;

    build_default_queue(&queue);

    assert(queue_size(&queue) == 4);
    assert(*(int *)queue_peek(&queue) == 42);

    queue_destroy(&queue);

    assert(queue_size(&queue) == 0);
    assert(queue_peek(&queue) == NULL);
}

static void build_default_queue(Queue *queue) {

    int *value1, *value2, *value3, *value4;

    value1 = malloc(sizeof(int));
    assert(value1 != NULL);
    *value1 = 42;

    value2 = malloc(sizeof(int));
    assert(value2 != NULL);
    *value2 = 24;

    value3 = malloc(sizeof(int));
    assert(value3 != NULL);
    *value3 = 52;
    
    value4 = malloc(sizeof(int));
    assert(value4 != NULL);
    *value4 = 10;

    queue_init(queue, free);

    assert(queue_enqueue(queue, value1) == 0);
    assert(queue_enqueue(queue, value2) == 0);
    assert(queue_enqueue(queue, value3) == 0);
    assert(queue_enqueue(queue, value4) == 0);
}

