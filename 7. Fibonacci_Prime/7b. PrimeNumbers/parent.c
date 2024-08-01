/*
7. b). Write a program to generate and print Prime numbers between a given range (between M & N) with the following requirements:
- M& N should be passed as command line arguments.
- Error checking should be done to verify the required number of arguments at the command line.
- Parent program should create a child and distribute the task of generating Prime numbers to its child.
- The code for generating Prime numbers should reside in different program.
- Child should write the generated Prime numbers to a shared memory.
- Parent process has to print by retrieving the Prime numbers from the shared memory.
i. Implement the above using shm _open and mmap.
Note: Shared object should be removed at the end in the program.
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
 
int main(int arguementCount, char *arguementVector[]) {
    int i, k, n1, n2, sharedMemoryFileDescriptor, j;
    const int SIZE = 4096;
    pid_t processID;
    void *ptr;

    if (arguementCount > 2) {
        sscanf(arguementVector[1], "%d", &i);
        sscanf(arguementVector[2], "%d", &j);
        if (i < 2) {
            printf("Error input: %d\n", i);
            return 0;
        }
    } else {
        printf("Error: Minimum of two arguments must be passed as command line arguments!");
        exit(0);
    }

    processID = fork();
    if (processID == 0) {
        execlp("./child.c", "prime", arguementVector[1], arguementVector[2], NULL);
    } else if (processID > 0) {
        wait(NULL);
        printf("\nParent: child complete!\n");
        sharedMemoryFileDescriptor = shm_open("OS", O_RDONLY, 0666);
        ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, sharedMemoryFileDescriptor, 0);
        printf("%s", (char *) ptr);
        shm_unlink("OS");
    }

    return 0;
}
