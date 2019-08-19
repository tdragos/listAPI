#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "list.h"

pthread_mutex_t mutex;

void print_node(node *NODE)
{
    printf("%d ", NODE->value);
}

//visit each node and call the callback print
void print_list(node *HEAD)
{
    pthread_mutex_lock(&mutex);
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
    pthread_mutex_unlock(&mutex);
}

//go to the end node and link it with the new one
node * insert(node *HEAD, int value)
{
    pthread_mutex_lock(&mutex);
    node *tmp = NULL;
    tmp = (struct node *)malloc(sizeof(node));
    tmp->value = value;
    tmp->callback_print = &print_node;
    tmp->next = NULL;

    if (HEAD == NULL) {
        HEAD = tmp;
        pthread_mutex_unlock(&mutex);
        return HEAD;
    }

    node *aux = HEAD;
    while (aux->next != NULL)
        aux = aux->next;
    aux->next = tmp;

    pthread_mutex_unlock(&mutex);
    return HEAD;
}

//keep a pointer to the node before the one we will
//delete and link it to the next one
node * delete(node *HEAD, int value)
{
    pthread_mutex_lock(&mutex);
    if (HEAD == NULL) {
        pthread_mutex_unlock(&mutex);
        return HEAD;
    }

    node *aux = HEAD;
    node *prev = HEAD;

    while (aux != NULL && aux->value != value) {
        prev = aux;
        aux = aux->next;
    }

    if (aux == HEAD) {
        prev = aux->next;
        free(aux);
        pthread_mutex_unlock(&mutex);
        return prev;
    }

    if (aux != NULL) {
        prev->next = aux->next;
        free(aux);
        pthread_mutex_unlock(&mutex);
        return HEAD;
    }

    pthread_mutex_unlock(&mutex);
    return HEAD;
}

//we sort the list by changing the values, not by
//changing the pointers
node * sort_list(node *HEAD)
{
    pthread_mutex_lock(&mutex);
    node *itr1 = HEAD;
    node *itr2;

    while (itr1 != NULL) {
        itr2 = itr1->next;
        while (itr2 != NULL) {
            if (itr1->value > itr2->value) {
                //change the values
                int swp = itr1->value;
                itr1->value = itr2->value;
                itr2->value = swp;
            }
            itr2 = itr2->next;
        }
        itr1 = itr1->next;
    }

    pthread_mutex_unlock(&mutex);
    return HEAD;
}

//free the memory for each node
void flush_list(node **HEAD)
{
    pthread_mutex_lock(&mutex);
    node *aux = *HEAD;
    node *prev = *HEAD;

    while (aux) {
        prev = aux;
        aux = aux->next;
        free(prev);
    }

    *HEAD = NULL;
    pthread_mutex_unlock(&mutex);
}
