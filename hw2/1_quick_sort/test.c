#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "qsort.h"
#include "stack.h"

/* Verify if list is order */
static bool list_is_ordered(struct list_head *head)
{
    if (!head || list_empty(head))
        return true;

    struct list_head *cur;
    list_for_each (cur, head) {
        if (cur->next == head)
            break;
        node_t *a = list_entry(cur, node_t, list);
        node_t *b = list_entry(cur->next, node_t, list);
        if (a->value > b->value) {
            printf("%ld, %ld\n", a->value, b->value);
            return false;
        }
    }
    return true;
}

/* shuffle array, only work if n < RAND_MAX */
void shuffle(int *array, size_t n)
{
    if (n <= 0)
        return;

    for (size_t i = 0; i < n - 1; i++) {
        size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
        int t = array[j];
        array[j] = array[i];
        array[i] = t;
    }
}


void show(struct list_head *head)
{
    node_t *cur;
    list_for_each_entry (cur, head, list)
        printf("%ld ", cur->value);
    printf("\n");
}

int main(int argc, char **argv)
{
    size_t count = 100000;

    long int time = 0;

    // // avg case
    struct list_head *list = list_new();

    for (int j = 0; j < count / 2; ++j)
        list_insert_head(list, j);

    for (int j = count - 1; j >= count / 2; --j)
        list_insert_head(list, j);


    time = quick_sort(&list);
    assert(list_is_ordered(list));

    list_free(list);

    printf("quick sort time (avg.  case): %ld\n", time);

    // best case
    list = list_new();

    for (int j = 0; j < count; ++j)
        list_insert_head(list, j);

    quick_sort(&list);
    assert(list_is_ordered(list));

    list_free(list);

    printf("quick sort time (worst case): %ld\n", time);

    // worst case
    list = list_new();

    for (size_t j = count; j > 0; --j)
        list_insert_head(list, j);

    time = quick_sort(&list);
    assert(list_is_ordered(list));

    list_free(list);

    printf("quick sort time (best  case): %ld\n", time);


    return 0;
}