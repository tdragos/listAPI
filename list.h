#ifndef NODE_MODULE
#define NODE_MODULE

typedef struct node {
    int value;
    void (*callback_print)(struct node *NODE);
    struct node *next;
} node;

void print_list(node *HEAD);

node * insert(node *HEAD, int value);

node * delete(node *HEAD, int value);

node * sort_list(node *HEAD);

void flush_list(node **HEAD);

#endif /* NODE_MODULE */
