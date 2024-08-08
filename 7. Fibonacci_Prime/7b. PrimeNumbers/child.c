#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include<stdlib.h>
#include <math.h>


int main(int argc, char *argv[]) {
    void *ptr;
    int shm_fd = shm_open("VSS", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, 4096);
    ptr = mmap(0, 4096, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    printf("CHILD:\n");
    int i = atoi(argv[1]);
    int j = atoi(argv[2]);
    int flag = 0;
    printf("The prime numbers in the range %d and %d are:\n", i, j);
    for (int num = i; num <= j; num++) {
        flag = 0;
        for (int k = 2; k <= num / 2; k++) {
            if (num % k == 0) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            printf("%d\t", num);
        }
    }
    printf("\n");
}
