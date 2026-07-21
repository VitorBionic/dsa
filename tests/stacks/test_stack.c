#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "stacks/stack.h"
#include "lists/list.h"

static void build_default_stack(Stack *stack);
static void test_stack_init(void);
static void test_push_one_element(void);
static void test_push_four_elements(void);
static void test_pop_one_element(void);
static void test_pop_four_elements(void);
static void test_stack_destroy(void);

int main(void) {
    
    test_stack_init();
    test_push_one_element();
    test_push_four_elements();
    test_pop_one_element();
    test_pop_four_elements();
    test_stack_destroy();
    
    puts("All stack tests passed!");

    return 0;
}

static void test_stack_init(void) {
    Stack stack;

    stack_init(&stack, free);

    assert(stack_size(&stack) == 0);
    assert(stack_peek(&stack) == NULL);

    stack_destroy(&stack);
}

static void test_push_one_element(void) {
    Stack stack;
    int *value;

    value = malloc(sizeof(int));
    assert(value != NULL);
    *value = 42;

    stack_init(&stack, free);

    assert(stack_peek(&stack) == NULL);

    assert(stack_push(&stack, value) == 0);

    assert(stack_size(&stack) == 1);
    assert(*(int *)stack_peek(&stack) == 42);

    stack_destroy(&stack);
}

static void test_push_four_elements(void) {
    Stack stack;
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

    stack_init(&stack, free);

    assert(stack_push(&stack, value1) == 0);
    assert(stack_push(&stack, value2) == 0);
    assert(stack_push(&stack, value3) == 0);
    assert(stack_push(&stack, value4) == 0);

    ListElmt *current;

    assert(stack_size(&stack) == 4);
    assert(*(int *)stack_peek(&stack) == 10);

    current = list_head(&stack);

    // 10, 52, 24, 42
    assert(*(int *)list_data(current) == 10);
    current = list_next(current);
    assert(*(int *)list_data(current) == 52);
    current = list_next(current);
    assert(*(int *)list_data(current) == 24);
    current = list_next(current);
    assert(*(int *)list_data(current) == 42);

    stack_destroy(&stack);

}

static void test_pop_one_element(void) {
    Stack stack;

    build_default_stack(&stack);
    assert(stack_size(&stack) == 4);
    assert(*(int *)stack_peek(&stack) == 10);

    int *data;

    assert(stack_pop(&stack, (void **)&data) == 0);

    assert(*data == 10);
    free(data);

    assert(stack_size(&stack) == 3);
    assert(*(int *)stack_peek(&stack) == 52);

    ListElmt *current;

    current = list_head(&stack);

    assert(*(int *)list_data(current) == 52);
    current = list_next(current);
    assert(*(int *)list_data(current) == 24);
    current = list_next(current);
    assert(*(int *)list_data(current) == 42);

    stack_destroy(&stack);
}

static void test_pop_four_elements(void) {
    Stack stack;

    build_default_stack(&stack);

    assert(stack_size(&stack) == 4);
    assert(*(int *)stack_peek(&stack) == 10);

    int *data;

    assert(stack_pop(&stack, (void **)&data) == 0);

    assert(*data == 10);
    free(data);

    assert(stack_size(&stack) == 3);
    assert(*(int *)stack_peek(&stack) == 52);

    assert(stack_pop(&stack, (void **)&data) == 0);

    assert(*data == 52);
    free(data);

    assert(stack_size(&stack) == 2);
    assert(*(int *)stack_peek(&stack) == 24);

    assert(stack_pop(&stack, (void **)&data) == 0);

    assert(*data == 24);
    free(data);

    assert(stack_size(&stack) == 1);
    assert(*(int *)stack_peek(&stack) == 42);

    assert(stack_pop(&stack, (void **)&data) == 0);

    assert(*data == 42);
    free(data);

    assert(stack_size(&stack) == 0);
    assert(stack_peek(&stack) == NULL);

    stack_destroy(&stack);
}

static void test_stack_destroy(void) {
    Stack stack;

    build_default_stack(&stack);

    assert(stack_size(&stack) == 4);
    assert(*(int *)stack_peek(&stack) == 10);

    stack_destroy(&stack);

    assert(stack_size(&stack) == 0);
    assert(stack_peek(&stack) == NULL);
}

static void build_default_stack(Stack *stack) {

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

    stack_init(stack, free);

    assert(stack_push(stack, value1) == 0);
    assert(stack_push(stack, value2) == 0);
    assert(stack_push(stack, value3) == 0);
    assert(stack_push(stack, value4) == 0);
}

