#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *threadfun(); // the Thread routine with no parameters
int i, j, n; // data shared by threads

void main() {
    pthread_t T1; // thread id
    pthread_create(&T1, NULL, threadfun, NULL); // create thread
    // pthread_create(&tid, &attr, threadfun, args);
    // pthread_join(T1, NULL); // the main thread waits for child thread to complete
    printf("Inside main thread\n");
    for (i = 10; i <= 15; i++) {
        printf("i=%d\n", i);
        sleep(1);
    }
    // pthread_exit(NULL); // wait for thread to exit
}

void *threadfun() {
    printf("inside thread\n");
    for (j = 1; j <= 5; j++) {
        printf("j=%d\n", j);
        sleep(1);
    }
}
