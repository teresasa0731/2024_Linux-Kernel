#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
    for(size_t cnt = 10; cnt <= 100000; cnt*=10){
        struct list_head *list = list_new();

        size_t count = cnt;

        int *test_arr = malloc(sizeof(int) * count);

        for (int i = 0; i < count; ++i)
            test_arr[i] = i;
        shuffle(test_arr, count);

        while (count--)
            list_insert_head(list, test_arr[count]);

        long int max_level = quick_sort(&list);
        assert(list_is_ordered(list));
        // show(list);

        list_free(list);

        free(test_arr);

        printf("size = %ld\tmax level %ld\n", cnt, max_level);
    }
    return 0;
}