#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <math.h>
#include <string.h>

int main(int argc, char *argv[]) {
    void *ptr;
    int shm_fd = shm_open("VSS", O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open failed");
        exit(1);
    }

    ftruncate(shm_fd, 4096); // Set size of shared memory
    ptr = mmap(0, 4096, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    int i = atoi(argv[1]);
    int j = atoi(argv[2]);
    int flag;

    sprintf(ptr, "The prime numbers in the range %d and %d are:\n", i, j); // Write header to shared memory
    ptr += strlen(ptr); // Move pointer to the end of the written header

    for (int num = i; num <= j; num++) {
        flag = 0;
        for (int k = 2; k <= num / 2; k++) {
            if (num % k == 0) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            sprintf(ptr, "%d\t", num); // Write prime number to shared memory
            ptr += strlen(ptr); // Move pointer to the end of the written number
        }
    }

    sprintf(ptr, "\n"); // Add a newline at the end

    munmap(ptr, 4096); // Unmap shared memory
    close(shm_fd); // Close shared memory file descriptor

    return 0;
}