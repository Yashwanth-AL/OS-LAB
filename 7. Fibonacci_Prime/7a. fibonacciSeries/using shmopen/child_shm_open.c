// child.c
#include <sys/types.h>      // Provides data types used in system calls
#include <sys/wait.h>       // Provides macros for waiting, process synchronization
#include <stdio.h>          // Provides input/output functions like printf
#include <string.h>      
#include <unistd.h>         // Provides access to the POSIX operating system API, includes functions like fork, exec, etc.
#include <sys/shm.h>        // Provides functions for shared memory operations
#include <sys/stat.h>       // Provides definitions for file status and permissions
#include <fcntl.h>          // Provides file control options
#include <sys/mman.h>       // Provides memory management declarations, includes functions like mmap, munmap
#include <stdlib.h>         // Provides general utility functions like atoi


int main(int argc, char *argv[]) {
    int k = 2, n1, n2, n3;
    int shm_fd = shm_open("VSS", O_CREAT | O_RDWR, 0666);  //file descriptor
    ftruncate(shm_fd, 4096);  // file truncate - sets the size of the shared memory
    void *ptr = mmap(0, 4096, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    //0 - starting address (may be chosen by the processor)
    //PROT_WRITE - protection for writing 
    printf("CHILD:\n");
    int i = atoi(argv[1]); // ASCII to integer
    n1 = 0;
    n2 = 1;
    sprintf(ptr, "%d ", n1);
    ptr += strlen(ptr);
    printf("%d ", n1);
    sprintf(ptr, "%d ", n2);
    ptr += strlen(ptr);
    printf("%d ", n2);
    while (k != i) {
        n3 = n1 + n2;
        sprintf(ptr, "%d ", n3);
        printf("%d ", n3);
        n1 = n2;
        n2 = n3;
        ptr += strlen(ptr);
        k++;
    }
}
