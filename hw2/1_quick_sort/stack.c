#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "stack.h"

struct list_head *list_new()
{
    struct list_head *new_head = malloc(sizeof(struct list_head));
    if (!new_head)
        return NULL;
    INIT_LIST_HEAD(new_head);
    return new_head;
}

int list_length(struct list_head *head)
{
    if (!head)
        return 0;

    int size = 0;
    struct list_head *cur;
    list_for_each (cur, head)
        size++;
    return size;
}

bool list_insert_head(struct list_head *head, int n)
{
    if (!head)
        return false;
    node_t *new_node = malloc(sizeof(node_t));
    if (!new_node)
        return false;
    INIT_LIST_HEAD(&new_node->list);
    new_node->value = n;
    list_add(&new_node->list, head);
    return true;
}

node_t *list_remove_head(struct list_head *head)
{
    if (!head || list_empty(head))
        return NULL;

    node_t *f = list_first_entry(head, node_t, list);
    list_del(&f->list);
    return f;
}

void list_free(struct list_head *head)
{
    if (!head)
        return;
    node_t *entry, *safe;
    list_for_each_entry_safe (entry, safe, head, list) {
        free(entry);
    }
    free(head);
    head = NULL;
    return;
}