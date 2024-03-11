#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "qlist.h"

void list_add(node_t **list, node_t *new_node)
{
    new_node->next = *list;
    *list = new_node;
}

node_t *list_tail(node_t **left)
{
    while ((*left) && (*left)->next)
        left = &((*left)->next);  // AAAA
    return *left;
}

int list_length(node_t **left)
{
    int n = 0;
    while (*left) {
        ++n;
        left = &((*left)->next);  // BBBB
    }
    return n;
}

node_t *list_construct(node_t *list, int n)
{
    node_t *node = malloc(sizeof(node_t));
    node->next = list;
    node->value = n;
    return node;
}

void list_free(node_t **list)
{
    node_t *node = (*list)->next;
    while (*list) {
        free(*list);
        *list = node;
        if (node)
            node = node->next;
    }
}