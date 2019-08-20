#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "list.h"

pthread_mutex_t mutex;

void print_node(node *NODE)
{
    printf("%d ", NODE->value);
}

/**
 * print the list by visiting all nodes and call the
 * callback print stored in each node
 * input: the first node of the list
 */
void print_list(node *HEAD)
{
    pthread_mutex_lock(&mutex);
    if(HEAD == NULL) {
        printf("The list is empty\n");
        pthread_mutex_unlock(&mutex);
        return;
    }

    node *aux = HEAD;
    while(aux != NULL) {
        //call the callback print function
        (*aux->callback_print)(aux);
        aux = aux->next;
    }
    printf("\n");
    pthread_mutex_unlock(&mutex);
}

/**
 * insert a node at the end of the list. We go to
 * the last node and link it with the new one
 * input: the first node of the list and the value
 *        for the new node
 */
void insert(node **HEAD, int value)
{
    pthread_mutex_lock(&mutex);
    node *tmp = NULL;
    tmp = (struct node *)malloc(sizeof(node));
    tmp->value = value;
    tmp->callback_print = &print_node;
    tmp->next = NULL;

    if (*HEAD == NULL) {
        *HEAD = tmp;
        pthread_mutex_unlock(&mutex);
        return;
    }

    node *aux = *HEAD;
    while (aux->next != NULL)
        aux = aux->next;
    aux->next = tmp;

    pthread_mutex_unlock(&mutex);
    return;
}

/**
 * delete the node with the given value from the list.
 * We keep the node before the one that will be deleted
 * and we link it to the one after the node that will
 * be deleted.
 * input: the first node of the list and the value of
 *        the node that will be deleted
 */
void delete(node **HEAD, int value)
{
    pthread_mutex_lock(&mutex);
    if (*HEAD == NULL) {
        pthread_mutex_unlock(&mutex);
        return;
    }

    node *aux = *HEAD;
    node *prev = *HEAD;

    while (aux != NULL && aux->value != value) {
        prev = aux;
        aux = aux->next;
    }

    //check if we have to delete the first node
    if (aux == *HEAD) {
        prev = aux->next;
        free(aux);
        *HEAD = prev;
        pthread_mutex_unlock(&mutex);
        return;
    }

    if (aux != NULL) {
        prev->next = aux->next;
        free(aux);
        pthread_mutex_unlock(&mutex);
        return;
    }

    pthread_mutex_unlock(&mutex);
    return;
}

/**
 * function that sorts the list in O(n^2). We sort the
 * list by changing the values of the nodes, not by
 * swapping the nodes.
 * input: the first node of the list
 */
void sort_list(node **HEAD)
{
    pthread_mutex_lock(&mutex);
    node *itr1 = *HEAD;
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
    return;
}

/**
 * free the memory for each node in our list
 * input: the first node of the list
 */
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
