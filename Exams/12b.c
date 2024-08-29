/* This program provides a possible solution for first readers writers problem using mutex and semaphore. There are 3 readers and 3 writers to demonstrate the solution. */

// to compile: gcc filename.c -pthread

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

sem_t wrt;
pthread_mutex_t mutex;
int cnt = 1;
int numreader = 0;

void *writer(void *wno) {
    sem_wait(&wrt);
    // Critical section for writers
    cnt = cnt * 2;
    printf("Writer %d modified cnt to %d\n", (*((int *)wno)), cnt);
    sem_post(&wrt);
}

void *reader(void *rno) {

    pthread_mutex_lock(&mutex);// Reader acquires the lock before modifying numreader
    numreader++;
    if (numreader == 1) {
        sem_wait(&wrt); // If this is the first reader, it will block the writer
    }
    pthread_mutex_unlock(&mutex);

    // Reading Section
    printf("Reader %d: read cnt as %d\n", *((int *)rno), cnt);

    
    pthread_mutex_lock(&mutex);// Reader acquires the lock before modifying numreader
    numreader--;
    if (numreader == 0) {
        sem_post(&wrt); // If this is the last reader, it will wake up the writer.
    }
    pthread_mutex_unlock(&mutex);
}

int main()
{
    pthread_t read[3], write[3];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt, 0, 1);
    int a[3] = {1, 2, 3}; // Just used for numbering the reader and writer

    for (int i = 0; i < 3; i++) {
        pthread_create(&read[i], NULL, (void *)reader, (void *)&a[i]);
    }
    for (int i = 0; i < 3; i++) {
        pthread_create(&write[i], NULL, (void *)writer, (void *)&a[i]);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(read[i], NULL);
    }
    for (int i = 0; i < 3; i++) {
        pthread_join(write[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);
    return 0;
}
