#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <sys/mman.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Error: Minimum of two arguments must be passed as command line arguments!\n");
        exit(0);
    }

    int start = atoi(argv[1]);
    int end = atoi(argv[2]);

    if (start < 2 || end < start) {
        printf("Error input: %d %d\n", start, end);
        return 0;
    }

    pid_t pid = fork();

    if (pid == 0) { 
        execlp("./child", "./child", argv[1], argv[2], NULL);
        perror("execlp failed");
        exit(1);
    } else if (pid > 0) { 
        wait(NULL);
        printf("\nParent: child complete!\n");

        int shm_fd = shm_open("VSS", O_RDONLY, 0666); 
        void *ptr = mmap(0, 4096, PROT_READ, MAP_SHARED, shm_fd, 0);

        printf("Parent printing:\n%s", (char *)ptr); 

        shm_unlink("VSS"); 
    }

    return 0;
}
