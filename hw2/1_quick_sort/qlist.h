#ifndef HW2_QLIST_H
#define HW2_QLIST_H

/* linked list node structure */
typedef struct __node {
    struct __node *left, *right;
    struct __node *next;
    long value;
} node_t;


/* Linked list operation */
void list_add(node_t **list, node_t *new_node);

node_t *list_tail(node_t **left);

int list_length(node_t **left);

node_t *list_construct(node_t *list, int n);

void list_free(node_t **list);

#endif