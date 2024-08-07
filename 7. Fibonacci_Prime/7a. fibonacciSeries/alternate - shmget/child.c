#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>

// Define the structure for shared memory
typedef struct {
    int count;     // Number of Fibonacci numbers to generate
    int fib[100];  // Array to hold Fibonacci numbers (adjust size as needed)
} fib_shared_t;

int main() {
    key_t key = 1234;
    int shmid = shmget(key, sizeof(fib_shared_t), 0666);
    fib_shared_t* shm_ptr = (fib_shared_t*) shmat(shmid, NULL, 0666);

    printf("[CHILD] Attached to shared memory with key = %d, id = %d, address = %p\n", key, shmid, shm_ptr);

    int n = shm_ptr->count;
    if (n <= 0) {
        printf("[CHILD] Invalid number of Fibonacci numbers requested: %d\n", n);
        return 1;
    }

    // Generate Fibonacci numbers
    if (n > 0) shm_ptr->fib[0] = 0;
    if (n > 1) shm_ptr->fib[1] = 1;

    for (int i = 2; i < n; i++) {
        shm_ptr->fib[i] = shm_ptr->fib[i - 1] + shm_ptr->fib[i - 2];
    }

    printf("[CHILD] Finished generating Fibonacci sequence\n");

    shmdt((void*) shm_ptr); // Detach from shared memory
    return 0;
}
