#ifndef NODE_MODULE
#define NODE_MODULE

typedef struct node {
    int value;
    void (*callback_print)(struct node *NODE);
    struct node *next;
} node;

void print_list(node *HEAD);

//insert node at the end of the list
node * insert(node *HEAD, int value);

//delete the node with the given value
node * delete(node *HEAD, int value);

//sort the list
node * sort_list(node *HEAD);

//emmpty the list
void flush_list(node **HEAD);

#endif /* NODE_MODULE */
