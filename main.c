#include <stdio.h>
#include <pthread.h>

#include "list.h"

node *HEAD = NULL;

pthread_mutex_t mutex;

void *thread1()
{
    pthread_mutex_lock(&mutex);
    printf("Thread1: insert 2\n");
    HEAD = insert(HEAD, 2);
    pthread_mutex_unlock(&mutex);
    
    pthread_mutex_lock(&mutex);
    printf("Thread1: insert 4\n");
    HEAD = insert(HEAD, 4);
    pthread_mutex_unlock(&mutex);
    
    pthread_mutex_lock(&mutex);
    printf("Thread1: insert 10\n");
    HEAD = insert(HEAD, 10);
    pthread_mutex_unlock(&mutex);
    
    pthread_mutex_lock(&mutex);
    printf("Thread1: delete 2\n");
    HEAD = delete(HEAD, 2);
    pthread_mutex_unlock(&mutex);
    
    pthread_mutex_lock(&mutex);
    printf("Thread1: sort list\n");
    HEAD = sort_list(HEAD);
    pthread_mutex_unlock(&mutex);
    
    pthread_mutex_lock(&mutex);
    printf("Thread1: delete 10\n");
    HEAD = delete(HEAD, 10);
    pthread_mutex_unlock(&mutex);
    
    pthread_mutex_lock(&mutex);
    printf("Thread1: delete 5\n");
    HEAD = delete(HEAD, 5);
    pthread_mutex_unlock(&mutex);
    
    return NULL;
}

void *thread2()
{
    pthread_mutex_lock(&mutex);
    printf("Thread2: insert 11\n");
    HEAD = insert(HEAD, 11);
    pthread_mutex_unlock(&mutex);
    
    pthread_mutex_lock(&mutex);
    printf("Thread2: insert 1\n");
    HEAD = insert(HEAD, 1);
    pthread_mutex_unlock(&mutex);
    
    pthread_mutex_lock(&mutex);
    printf("Thread2: delete 11\n");
    HEAD = delete(HEAD, 11);
    pthread_mutex_unlock(&mutex);
    
    pthread_mutex_lock(&mutex);
    printf("Thread2: insert 8\n");
    HEAD = insert(HEAD, 8);
    pthread_mutex_unlock(&mutex);
    
    pthread_mutex_lock(&mutex);
    printf("Thread2: print list\n");
    print_list(HEAD);
    pthread_mutex_unlock(&mutex);
    
    return NULL;
}

void *thread3()
{
    pthread_mutex_lock(&mutex);
    printf("Thread3: insert 30\n");
    HEAD = insert(HEAD, 30);
    pthread_mutex_unlock(&mutex);
    
    pthread_mutex_lock(&mutex);
    printf("Thread3: insert 25\n");
    HEAD = insert(HEAD, 25);
    pthread_mutex_unlock(&mutex);
    
    pthread_mutex_lock(&mutex);
    printf("Thread3: insert 100\n");
    HEAD = insert(HEAD, 100);
    pthread_mutex_unlock(&mutex);
    
    pthread_mutex_lock(&mutex);
    printf("Thread3: sort list\n");
    HEAD = sort_list(HEAD);
    pthread_mutex_unlock(&mutex);
    
    pthread_mutex_lock(&mutex);
    printf("Thread3: print list\n");
    print_list(HEAD);
    pthread_mutex_unlock(&mutex);
    
    pthread_mutex_lock(&mutex);
    printf("Thread3: delete 100\n");
    HEAD = delete(HEAD, 100);
    pthread_mutex_unlock(&mutex);
    
    return NULL;
}

int main(void)
{
    pthread_t thread_ids[3];
    
    pthread_create(&thread_ids[0], NULL, thread1, NULL);
    pthread_create(&thread_ids[1], NULL, thread2, NULL);
    pthread_create(&thread_ids[2], NULL, thread3, NULL);
    
    for (int i = 0; i < 3; i++)
        pthread_join(thread_ids[i], NULL);

    printf("\nThe list after threads end\n");
    print_list(HEAD);
    flush_list(&HEAD);
    print_list(HEAD);
    
    return 0;
}
