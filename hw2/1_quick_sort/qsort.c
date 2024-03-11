#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "list.h"
#include "qsort.h"
#include "stack.h"

int count(int size) {
    int cnt = 0;
    while (size != 0)
    {
        cnt++;
        size /= 10;
    }
    return cnt * 10;
}

long int quick_sort(struct list_head **head)
{
    clock_t time = clock();

    if (!(*head) || list_empty(*head))
        return clock() - time;

    int n = list_length(*head);
    int i = 0;
    int max_level = count(n);
    int max = 0;    // max_level test
    struct list_head *begin[max_level];
    for (int i = 1; i < max_level; i++)
        begin[i] = list_new();
    struct list_head *result = list_new();
    struct list_head *left = list_new(), *right = list_new();

    begin[0] = *head;

    while (i >= 0) {
        struct list_head *L = begin[i]->next, *R = begin[i]->prev;
        if (L != R) {
            node_t *pivot = list_remove_head(begin[i]);

            node_t *entry, *safe;
            list_for_each_entry_safe (entry, safe, begin[i], list) {
                list_del(&entry->list);
                if (entry->value > pivot->value) {
                    list_add(&entry->list, right);
                } else {
                    list_add(&entry->list, left);
                }
            }

            list_splice_init(left, begin[i]);
            list_add(&pivot->list, begin[i + 1]);
            list_splice_init(right, begin[i + 2]);

            i += 2;
            max = i > max ? i : max;
        } else {
            if (list_is_singular(begin[i]))
                list_splice_init(begin[i], result);
            i--;
        }
    }

    for (int i = 0; i < max_level; i++)
        list_free(begin[i]);
    list_free(left);
    list_free(right);

    *head = result;

    time = clock() - time;

    return max;
}