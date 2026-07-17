#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "lists/clist.h"

static void build_default_list(CList *list);
static void test_clist_init(void);
static void test_insert_one_next_element(void);
static void test_insert_four_elements(void);
static void test_remove_head(void);
static void test_remove_after_head(void);
static void test_clist_destroy(void);

int main(void) {
    
    test_clist_init();
    test_insert_one_next_element();
    test_insert_four_elements();
    test_remove_head();
    test_remove_after_head();
    test_clist_destroy();
    
    puts("All circular singly linked list tests passed!");

    return 0;
}

static void test_clist_init(void) {
    CList list;

    clist_init(&list, free);

    assert(clist_size(&list) == 0);
    assert(clist_head(&list) == NULL);

    clist_destroy(&list);
}

static void test_insert_one_next_element(void) {
    CList list;
    int *value;

    value = malloc(sizeof(int));
    assert(value != NULL);
    *value = 42;

    clist_init(&list, free);

    assert(clist_ins_next(&list, NULL, value) == 0);

    assert(clist_size(&list) == 1);
    assert(clist_head(&list) != NULL);
    assert(clist_head(&list) == clist_head(&list)->next);
    assert(*(int *)clist_data(clist_head(&list)) == 42);

    clist_destroy(&list);
}

static void test_insert_four_elements(void) {
    CList list;
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

    clist_init(&list, free);

    assert(clist_ins_next(&list, NULL, value1) == 0);
    assert(clist_ins_next(&list, clist_head(&list), value2) == 0);
    assert(clist_ins_next(&list, clist_head(&list), value3) == 0);
    assert(clist_ins_next(&list, clist_next(clist_head(&list)), value4) == 0);

    CListElmt *current;

    assert(clist_size(&list) == 4);
    assert(clist_head(&list) != NULL);

    current = clist_head(&list);

    // 42, 52, 10, 24
    assert(*(int *)clist_data(current) == 42);
    current = clist_next(current);
    assert(*(int *)clist_data(current) == 52);
    current = clist_next(current);
    assert(*(int *)clist_data(current) == 10);
    current = clist_next(current);
    assert(*(int *)clist_data(current) == 24);
    current = clist_next(current);
    assert(*(int *)clist_data(current) == 42);

    clist_destroy(&list);

}

static void test_remove_head(void) {
    CList list;

    build_default_list(&list);

    CListElmt *current = clist_head(&list);
    int i;
    for (i = 0; i < 3; ++i)
        current = current->next;

    int *data;

    assert(clist_rem_next(&list, current, (void **)&data) == 0);

    assert(*data == 42);
    free(data);

    assert(clist_size(&list) == 3);

    current = clist_head(&list);

    assert(*(int *)clist_data(current) == 52);
    current = clist_next(current);
    assert(*(int *)clist_data(current) == 10);
    current = clist_next(current);
    assert(*(int *)clist_data(current) == 24);
    current = clist_next(current);
    assert(*(int *)clist_data(current) == 52);

    clist_destroy(&list);
}

static void test_remove_after_head(void) {
    CList list;

    build_default_list(&list);

    int *data;

    assert(clist_rem_next(&list, clist_next(clist_head(&list)), (void **)&data) == 0);

    assert(*data == 10);
    free(data);

    assert(clist_size(&list) == 3);

    CListElmt *current = clist_head(&list);

    assert(*(int *)clist_data(current) == 42);
    current = clist_next(current);
    assert(*(int *)clist_data(current) == 52);
    current = clist_next(current);
    assert(*(int *)clist_data(current) == 24);
    current = clist_next(current);
    assert(*(int *)clist_data(current) == 42);

    clist_destroy(&list);
}

static void test_clist_destroy(void) {
    CList list;

    build_default_list(&list);

    clist_destroy(&list);

    assert(clist_size(&list) == 0);
    assert(clist_head(&list) == NULL);
}

static void build_default_list(CList *list) {

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

    clist_init(list, free);

    assert(clist_ins_next(list, NULL, value1) == 0);
    assert(clist_ins_next(list, clist_head(list), value2) == 0);
    assert(clist_ins_next(list, clist_head(list), value3) == 0);
    assert(clist_ins_next(list, clist_next(clist_head(list)), value4) == 0);

}

