#include <stdlib.h>
#include <stdio.h>

#include "list.h"

void print_node(node *NODE)
{
    printf("%d ", NODE->value);
}

void print_list(node *HEAD)
{
    if(HEAD == NULL) {
        printf("The list is empty\n");
        return;
    }
    
    node *aux = HEAD;
    while(aux != NULL) {
        (*aux->callback_print)(aux);
        aux = aux->next;
    }
    printf("\n");
}

node * insert(node *HEAD, int value)
{
    node *tmp = NULL;
    tmp = (struct node *)malloc(sizeof(node));
    tmp->value = value;
    tmp->callback_print = &print_node;
    tmp->next = NULL;
    
    if (HEAD == NULL) {
        HEAD = tmp;
        return HEAD;
    }
    
    node *aux = HEAD;
    while (aux->next != NULL)
        aux = aux->next;
    aux->next = tmp;
    
    return HEAD;
}

node * delete(node *HEAD, int value)
{    
    if (HEAD == NULL)
        return HEAD;
    
    node *aux = HEAD;
    node *prev = HEAD;
    
    while (aux != NULL && aux->value != value) {
        prev = aux;
        aux = aux->next;
    }
    
    if (aux == HEAD) {
        prev = aux->next;
        free(aux);
        return prev;
    }
    
    if (aux != NULL) {
        prev->next = aux->next;
        free(aux);
        
        return HEAD;
    }
    
    return HEAD;
}

node * sort_list(node *HEAD)
{
    node *itr1 = HEAD;
    node *itr2;
    
    while (itr1 != NULL) {
        itr2 = itr1->next;
        while (itr2 != NULL) {
            if (itr1->value > itr2->value) {
                int swp = itr1->value;
                itr1->value = itr2->value;
                itr2->value = swp;
            }
            itr2 = itr2->next;
        }
        itr1 = itr1->next;
    }
    
    return HEAD;
}

void flush_list(node **HEAD)
{
    node *aux = *HEAD;
    node *prev = *HEAD;
    
    while (aux) {
        prev = aux;
        aux = aux->next;
        free(prev);
    }
    
    *HEAD = NULL;
}
