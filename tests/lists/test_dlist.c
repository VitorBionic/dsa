#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "lists/dlist.h"

static void test_dlist_init(void) {
    DList list;

    dlist_init(&list, free);

    assert(dlist_size(&list) == 0);
    assert(dlist_head(&list) == NULL);
    assert(dlist_tail(&list) == NULL);

    dlist_destroy(&list);
}

static void test_insert_one_next_element() {
    DList list;
    int *value;

    value = malloc(sizeof(int));
    assert(value != NULL);
    *value = 42;

    dlist_init(&list, free);

    assert(dlist_ins_next(&list, NULL, value) == 0);

    assert(dlist_size(&list) == 1);
    assert(dlist_head(&list) != NULL);
    assert(dlist_tail(&list) != NULL);
    assert(dlist_head(&list) == dlist_tail(&list));
    assert(dlist_prev(dlist_head(&list)) == NULL);
    assert(dlist_next(dlist_head(&list)) == NULL);
    assert(*(int *)dlist_data(dlist_head(&list)) == 42);

    dlist_destroy(&list);
}

static void test_insert_one_prev_element(void) {
    DList list;
    int *value;

    value = malloc(sizeof(int));
    assert(value != NULL);
    *value = 42;

    dlist_init(&list, free);

    assert(dlist_ins_prev(&list, NULL, value) == 0);

    assert(dlist_size(&list) == 1);
    assert(dlist_head(&list) != NULL);
    assert(dlist_tail(&list) != NULL);
    assert(dlist_head(&list) == dlist_tail(&list));
    assert(dlist_prev(dlist_head(&list)) == NULL);
    assert(dlist_next(dlist_head(&list)) == NULL);
    assert(*(int *)dlist_data(dlist_head(&list)) == 42);

    dlist_destroy(&list);
}

static void test_insert_four_elements(void) {
    DList list;
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

    dlist_init(&list, free);

    assert(dlist_ins_next(&list, NULL, value1) == 0);
    assert(dlist_ins_prev(&list, dlist_head(&list), value2) == 0);
    assert(dlist_ins_next(&list, dlist_tail(&list), value3) == 0);
    assert(dlist_ins_prev(&list, dlist_next(dlist_head(&list)), value4) == 0);

    DListElmt *current;

    assert(dlist_size(&list) == 4);
    assert(dlist_head(&list) != NULL);
    assert(dlist_tail(&list) != NULL);
    assert(dlist_prev(dlist_head(&list)) == NULL);
    assert(dlist_next(dlist_tail(&list)) == NULL);

    current = dlist_head(&list);

    // 24, 10, 42, 52 
    assert(*(int *)dlist_data(current) == 24);
    current = dlist_next(current);
    assert(*(int *)dlist_data(current) == 10);
    current = dlist_next(current);
    assert(*(int *)dlist_data(current) == 42);
    current = dlist_next(current);
    assert(*(int *)dlist_data(current) == 52);

    dlist_destroy(&list);

}

static void test_remove_head(void) {
    DList list;

    int *value1, *value2, *value3, *value4;
    int *data;

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

    dlist_init(&list, free);

    assert(dlist_ins_next(&list, NULL, value1) == 0);
    assert(dlist_ins_prev(&list, dlist_head(&list), value2) == 0);
    assert(dlist_ins_next(&list, dlist_tail(&list), value3) == 0);
    assert(dlist_ins_prev(&list, dlist_next(dlist_head(&list)), value4) == 0);

    assert(dlist_remove(&list, dlist_head(&list), (void **)&data) == 0);

    assert(*data == 24);
    free(data);

    assert(dlist_size(&list) == 3);

    DListElmt *current = dlist_head(&list);

    assert(*(int *)dlist_data(current) == 10);
    current = dlist_next(current);
    assert(*(int *)dlist_data(current) == 42);
    current = dlist_next(current);
    assert(*(int *)dlist_data(current) == 52);

    assert(dlist_prev(dlist_head(&list)) == NULL);
    assert(dlist_next(dlist_tail(&list)) == NULL);

    dlist_destroy(&list);
}

static void test_remove_after_head(void) {
    DList list;

    int *value1, *value2, *value3, *value4;
    int *data;

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

    dlist_init(&list, free);

    assert(dlist_ins_next(&list, NULL, value1) == 0);
    assert(dlist_ins_prev(&list, dlist_head(&list), value2) == 0);
    assert(dlist_ins_next(&list, dlist_tail(&list), value3) == 0);
    assert(dlist_ins_prev(&list, dlist_next(dlist_head(&list)), value4) == 0);

    assert(dlist_remove(&list, dlist_next(dlist_head(&list)), (void **)&data) == 0);

    assert(*data == 10);
    free(data);

    assert(dlist_size(&list) == 3);

    DListElmt *current = dlist_head(&list);

    assert(*(int *)dlist_data(current) == 24);
    current = dlist_next(current);
    assert(*(int *)dlist_data(current) == 42);
    current = dlist_next(current);
    assert(*(int *)dlist_data(current) == 52);

    dlist_destroy(&list);
}

static void test_dlist_destroy(void) {
    DList list;

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

    dlist_init(&list, free);

    assert(dlist_ins_next(&list, NULL, value1) == 0);
    assert(dlist_ins_prev(&list, dlist_head(&list), value2) == 0);
    assert(dlist_ins_next(&list, dlist_tail(&list), value3) == 0);
    assert(dlist_ins_prev(&list, dlist_next(dlist_head(&list)), value4) == 0);

    dlist_destroy(&list);

    assert(dlist_size(&list) == 0);
    assert(dlist_head(&list) == NULL);
    assert(dlist_tail(&list) == NULL);
}

int main(void) {
    
    test_dlist_init();
    test_insert_one_next_element();
    test_insert_one_prev_element();
    test_insert_four_elements();
    test_remove_head();
    test_remove_after_head();
    test_dlist_destroy();
    
    puts("All doubly linked list tests passed!");

    return 0;
}
