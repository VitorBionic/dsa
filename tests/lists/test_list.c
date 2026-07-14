#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "lists/list.h"

static void test_list_init(void)
{
    List list;

    list_init(&list, free);

    assert(list_size(&list) == 0);
    assert(list_head(&list) == NULL);
    assert(list_tail(&list) == NULL);

    list_destroy(&list);
}

static void test_insert_one_element(void)
{
    List list;
    int *value;

    value = malloc(sizeof(int));
    assert(value != NULL);
    *value = 42;

    list_init(&list, free);

    assert(list_ins_next(&list, NULL, value) == 0);

    assert(list_size(&list) == 1);
    assert(list_head(&list) != NULL);
    assert(list_tail(&list) != NULL);
    assert(list_head(&list) == list_tail(&list));
    assert(list_next(list_head(&list)) == NULL);
    assert(*(int *)list_data(list_head(&list)) == 42);

    list_destroy(&list);
}

static void test_insert_two_elements(void)
{
    List list;
    int *value1, *value2;

    value1 = malloc(sizeof(int));
    value2 = malloc(sizeof(int));

    assert(value1 != NULL);
    assert(value2 != NULL);

    *value1 = 42;
    *value2 = 24;

    list_init(&list, free);

    assert(list_ins_next(&list, NULL, value1) == 0);
    assert(list_ins_next(&list, list_head(&list), value2) == 0);

    assert(list_size(&list) == 2);
    assert(*(int *)list_data(list_head(&list)) == 42);
    assert(*(int *)list_data(list_next(list_head(&list))) == 24);
    assert(list_tail(&list) == list_next(list_head(&list)));

    list_destroy(&list);
}

static void test_remove_after_head(void)
{
    List list;
    int *value1, *value2;
    int *data;

    value1 = malloc(sizeof(int));
    value2 = malloc(sizeof(int));

    assert(value1 != NULL);
    assert(value2 != NULL);

    *value1 = 42;
    *value2 = 24;

    list_init(&list, free);

    list_ins_next(&list, NULL, value1);
    list_ins_next(&list, list_head(&list), value2);

    assert(list_rem_next(&list, list_head(&list), (void **)&data) == 0);

    assert(*data == 24);

    free(data);

    assert(list_size(&list) == 1);
    assert(list_head(&list) == list_tail(&list));
    assert(list_next(list_head(&list)) == NULL);
    assert(*(int *)list_data(list_head(&list)) == 42);

    list_destroy(&list);
}

static void test_list_destroy(void)
{
    List list;
    int *value;

    value = malloc(sizeof(int));
    assert(value != NULL);

    *value = 42;

    list_init(&list, free);

    list_ins_next(&list, NULL, value);

    list_destroy(&list);

    assert(list_size(&list) == 0);
    assert(list_head(&list) == NULL);
    assert(list_tail(&list) == NULL);
}

int main(void)
{
    test_list_init();
    test_insert_one_element();
    test_insert_two_elements();
    test_remove_after_head();
    test_list_destroy();

    puts("All singly linked list tests passed!");

    return 0;
}
