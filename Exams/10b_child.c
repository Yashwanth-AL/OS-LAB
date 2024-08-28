#include <stdio.h>          
#include <stdlib.h>         
#include <string.h>      
#include <unistd.h>         
#include <sys/shm.h>        
#include <fcntl.h>          
#include <sys/mman.h>       

int main(int argc, char *argv[]) {
    int shm_fd = shm_open("VSS", O_CREAT | O_RDWR, 0666);  
    ftruncate(shm_fd, 4096);  
    void *ptr = mmap(0, 4096, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    int start = atoi(argv[1]);
    int end = atoi(argv[2]);

    sprintf(ptr, "The prime numbers in the range %d and %d are:\n", start, end);
    ptr += strlen(ptr);

    for (int num = start; num <= end; num++) {
        int is_prime = 1;
        for (int i = 2; i <= num / 2; i++) {
            if (num % i == 0) {
                is_prime = 0;
                break;
            }
        }
        if (is_prime && num > 1) {
            sprintf(ptr, "%d\t", num);
            ptr += strlen(ptr);
        }
    }

    sprintf(ptr, "\n");

    munmap(ptr, 4096); 
    close(shm_fd); 

    return 0;
}
