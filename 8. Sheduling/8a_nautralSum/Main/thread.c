#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Structure to pass parameters to threads
typedef struct {
    int n;
} Node;

// Global variables to store results
int sum_result = 0;
unsigned long long factorial_result = 1;

// Function to calculate sum
void *calculate_sum(void *arg) {
    Node *data = (Node *)arg;
    int n = data->n;
    printf("[Thread 1] Calculating the sum of natural numbers up to %d...\n", n);
    sum_result = (n * (n + 1)) / 2;
    printf("[Thread 1] Sum calculated: %d\n", sum_result);
    pthread_exit(NULL);
}

// Function to calculate factorial
void *calculate_factorial(void *arg) {
    Node *data = (Node *)arg;
    int n = data->n;
    printf("[Thread 2] Calculating the factorial of %d...\n", n);
    factorial_result = 1;
    for (int i = 1; i <= n; i++) {
        factorial_result *= i;
    }
    printf("[Thread 2] Factorial calculated: %llu\n", factorial_result);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: Invalid input. Please provide a number.\n");
        return 1;
    }

    int n = atoi(argv[1]);
    if (n < 0) {
        printf("Error: Please enter a non-negative integer.\n");
        return 1;
    }

    pthread_t thread1, thread2;
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    Node data;
    data.n = n;

    // Create threads
    if (pthread_create(&thread1, &attr, calculate_sum, (void *)&data) != 0) {
        perror("Failed to create thread1");
        return 1;
    }

    if (pthread_create(&thread2, &attr, calculate_factorial, (void *)&data) != 0) {
        perror("Failed to create thread2");
        return 1;
    }

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Print results
    printf("Inside main thread\n");
    printf("Sum of natural numbers up to %d is: %d\n", n, sum_result);
    printf("Factorial of %d is: %llu\n", n, factorial_result);

    return 0;
}
