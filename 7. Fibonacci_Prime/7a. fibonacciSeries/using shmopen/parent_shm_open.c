#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

int main(int argc, char *argv[]) {
    // Check if the user passed a number (N) as a command-line argument
    if (argc < 2) {
        printf("Error: not passing N in command line\n");
        exit(0);
    }

    // Convert the argument from string to integer using atoi
    int N = atoi(argv[1]);

    // Validate the input
    if (N < 1) {
        printf("Error input: %d\n", N);
        return 0;
    }

    // Fork a child process
    pid_t pid = fork();

    if (pid == 0) { // CHILD PROCESS
        execlp("./child", "child", argv[1], NULL);
    } else if (pid > 0) { // PARENT PROCESS
        // Wait for the child process to complete
        wait(NULL);
        printf("\nPARENT: child completed\n");

        // Open the shared memory object created by the child
        int shm_fd = shm_open("VSS", O_RDONLY, 0666);

        // Map the shared memory object to the parent's address space
        void *ptr = mmap(0, 4096, PROT_READ, MAP_SHARED, shm_fd, 0);

        // Print the data stored in shared memory
        printf("Parent printing:\n");
        printf("%s\n", (char *)ptr);

        // Unlink the shared memory object
        shm_unlink("VSS");
    }

    return 0;
}
