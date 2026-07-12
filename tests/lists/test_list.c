#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "lists/list.h"

void test_insert_one_dynamic(void) {
    List list;

    int *value = malloc(sizeof(int));
    assert(value != NULL);

    *value = 42;

    list_init(&list, free);

    assert(list_size(&list) == 0);

    assert(list_ins_next(&list, NULL, value) == 0);

    assert(list_size(&list) == 1);

    assert(list_head(&list) != NULL);

    assert(list_tail(&list) != NULL);

    assert(list_head(&list) == list_tail(&list));

    assert(*(int *)list_data(list_head(&list)) == 42);

    list_destroy(&list);

    assert(list_size(&list) == 0);
    assert(list_head(&list) == NULL);
    assert(list_tail(&list) == NULL);
}

int main(void) {
    test_insert_one_dynamic();
    puts("Test singly linked list suceeded!");

    return 0;
}

