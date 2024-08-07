#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Define the structure for shared memory
typedef struct {
    int count;     // Number of Fibonacci numbers to generate
    int fib[100];  // Array to hold Fibonacci numbers (adjust size as needed)
} fib_shared_t;

int main() {
    key_t key = 1234;
    int shmid = shmget(key, sizeof(fib_shared_t), 0666 | IPC_CREAT);
    fib_shared_t* shm_ptr = (fib_shared_t*) shmat(shmid, NULL, 0666);

    printf("[PARENT] Created shared memory with key = %d, id = %d, address = %p\n", key, shmid, shm_ptr);
    printf("[PARENT] Enter the number of Fibonacci numbers to generate: ");
    scanf("%d", &shm_ptr->count);

    pid_t child_pid;
    if ((child_pid = fork()) == 0) {
        execlp("./child", "./child", NULL); // Execute child process
    } else {
        wait(NULL); // Wait for child process to finish
        printf("[PARENT] Child finished executing.\n");
        printf("[PARENT] The Fibonacci sequence is:\n");
        for (int i = 0; i < shm_ptr->count; i++)
            printf("%d ", shm_ptr->fib[i]);
        putchar('\n');

        shmdt((void*) shm_ptr); // Detach from shared memory
        shmctl(shmid, IPC_RMID, NULL); // Delete shared memory
        printf("[PARENT] Shared Memory Deleted\n");
    }

    return 0;
}
