#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "list.h"
#include "qsort.h"
#include "stack.h"

int count(int size)
{
    int cnt = 0;
    while (size != 0) {
        cnt++;
        size /= 10;
    }
    return cnt * 10;
}


static inline void list_swap(struct list_head *entry1, struct list_head *entry2)
{
    struct list_head *pos = entry2->prev;

    list_del(entry2);
    entry2->next = entry1->next;
    entry2->next->prev = entry2;
    entry2->prev = entry1->prev;
    entry2->prev->next = entry2;
    if (pos == entry1)
        pos = entry2;
    list_add(entry1, pos);
}

void random_pivot(struct list_head *head)
{
    if (!head || list_is_singular(head))
        return;
    int r = rand() % list_length(head);
    struct list_head *pick;
    list_for_each (pick, head) {
        if (r == 0)
            break;
        r--;
    }
    if (head->next != pick)
        list_swap(head->next, pick);
}


long int quick_sort(struct list_head **head)
{
    clock_t time = clock();

    if (!(*head) || list_empty(*head))
        return clock() - time;

    int n = list_length(*head);
    int i = 0;
    // int max_level = count(n);
    int max_level = 2 * n;
    int max = 0;  // max_level test
    struct list_head *begin[max_level];
    for (int i = 1; i < max_level; i++)
        begin[i] = list_new();
    struct list_head *result = list_new();
    struct list_head *left = list_new(), *right = list_new();

    begin[0] = *head;

    while (i >= 0) {
        struct list_head *L = begin[i]->next, *R = begin[i]->prev;
        if (L != R) {
            random_pivot(begin[i]);
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

    printf("max level = %d\t", max);

    return time;
}