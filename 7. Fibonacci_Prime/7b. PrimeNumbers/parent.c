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
 
int main(int argc, char *argv[]) {
    int i, k, n1, n2, shm_fd, j;
    void *ptr;

    if (argc > 2) {
        sscanf(argv[1], "%d", &i);
        sscanf(argv[2], "%d", &j);
        if (i < 2) {
            printf("Error input: %d\n", i);
            return 0;
        }
    } else {
        printf("Error: Minimum of two arguments must be passed as command line arguments!");
        exit(0);
    }

    pid_t pid = fork();
    if (pid == 0) {
        execlp("./child", "child", argv[1], argv[2], NULL);
    } else if (pid > 0) {
        wait(NULL);
        printf("\nParent: child complete!\n");
        shm_fd = shm_open("OS", O_RDONLY, 0666);
        ptr = mmap(0, 4096, PROT_READ, MAP_SHARED, shm_fd, 0);
        printf("%s", (char *) ptr);
        shm_unlink("OS");
    }

    return 0;
}
