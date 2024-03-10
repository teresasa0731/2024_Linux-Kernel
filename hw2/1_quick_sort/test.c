#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "qlist.h"
#include "qsort.h"

int test_cnt = 10000;

/* Verify if list is order */
static bool list_is_ordered(node_t *list)
{
    bool first = true;
    int value;
    while (list) {
        if (first) {
            value = list->value;
            first = false;
        } else {
            if (list->value < value)
                return false;
            value = list->value;
        }
        list = list->next;
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

void show(node_t *head)
{
    while (head) {
        printf("%ld ", head->value);
        head = head->next;
    }
    printf("\n");
}

long int test_avg(long int *arr){
    long long int avg = 0;
    for(int i = 0; i < test_cnt; i++)
        avg += arr[i];
    return avg / test_cnt;   
}

int main(int argc, char **argv)
{
    node_t *list = NULL;
    size_t count = 10000;

    long int time = 0;

    // avg case
    for (size_t j = 0; j < count/2; ++j)
        list = list_construct(list, j);

    for (size_t j = count-1 ; j >= count/2; --j)
        list = list_construct(list, j);

    time = quick_sort(&list);
    assert(list_is_ordered(list));

    list_free(&list);

    printf("quick sort time (avg.  case): %ld\n",time);

    // worst case

    for (size_t j = 0; j < count; ++j)
        list = list_construct(list, j);

    time = quick_sort(&list);
    assert(list_is_ordered(list));

    list_free(&list);

    printf("quick sort time (worst case): %ld\n",time);

    // best case

    for (size_t j = count; j > 0; --j)
        list = list_construct(list, j);

    time = quick_sort(&list);
    assert(list_is_ordered(list));

    list_free(&list);

    printf("quick sort time (best  case): %ld\n",time);
    

    return 0;
}