#include <stdio.h>
#include <pthread.h>

#include "list.h"

#define NUM_THREADS 3

node *HEAD = NULL;

pthread_barrier_t barrier;

void *thread_routine(void *arg)
{
    int thread_id = (int) arg;

    pthread_barrier_wait(&barrier);

    //each thread does different things
    if (thread_id == 1) {
        printf("Thread1: insert 2\n");
        HEAD = insert(HEAD, 2);

        printf("Thread1: insert 4\n");
        HEAD = insert(HEAD, 4);

        printf("Thread1: insert 10\n");
        HEAD = insert(HEAD, 10);

        printf("Thread1: delete 2\n");
        HEAD = delete(HEAD, 2);

        printf("Thread1: sort list\n");
        HEAD = sort_list(HEAD);

        printf("Thread1: delete 10\n");
        HEAD = delete(HEAD, 10);

        printf("Thread1: delete 5\n");
        HEAD = delete(HEAD, 5);
    }
    else if (thread_id == 2) {
        printf("Thread2: insert 11\n");
        HEAD = insert(HEAD, 11);

        printf("Thread2: insert 1\n");
        HEAD = insert(HEAD, 1);

        printf("Thread2: delete 11\n");
        HEAD = delete(HEAD, 11);

        printf("Thread2: insert 8\n");
        HEAD = insert(HEAD, 8);

        printf("Thread2: print list\n");
        print_list(HEAD);
    }
    else {
        printf("Thread3: insert 30\n");
        HEAD = insert(HEAD, 30);

        printf("Thread3: insert 25\n");
        HEAD = insert(HEAD, 25);

        printf("Thread3: insert 100\n");
        HEAD = insert(HEAD, 100);

        printf("Thread3: sort list\n");
        HEAD = sort_list(HEAD);

        printf("Thread3: print list\n");
        print_list(HEAD);

        printf("Thread3: delete 100\n");
        HEAD = delete(HEAD, 100);
    }

    return NULL;
}

int main(void)
{
    pthread_t thread_ids[3];
    pthread_barrier_init(&barrier, NULL, NUM_THREADS);

    //create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&thread_ids[i], NULL, thread_routine, (void *) i);
    }

    //wait for threads to end
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(thread_ids[i], NULL);

    //print the list and free the memory
    printf("\nThe list after threads end\n");
    print_list(HEAD);
    flush_list(&HEAD);
    print_list(HEAD);

    pthread_barrier_destroy(&barrier);

    return 0;
}
