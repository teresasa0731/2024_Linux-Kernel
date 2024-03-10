#ifndef HW2_STACK_H
#define HW2_STACK_H

#include "list.h"

typedef struct __node {
    long value;
    struct list_head list;
} node_t;

struct list_head *list_new();
int list_length(struct list_head *head);
bool list_insert_head(struct list_head *head, int n);
node_t *list_remove_head(struct list_head *head);
void list_free(struct list_head *head);

#endif