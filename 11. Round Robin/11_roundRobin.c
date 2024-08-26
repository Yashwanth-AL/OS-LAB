#include <stdio.h>
#include <stdlib.h>

typedef struct process {
    int processId;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;
    int responseTime;
    int remainingTime;
    int flag; //used to check whether the item is present in the queue or not
} Process;

void roundRobinScheduling(Process[], int, int);

int main() {
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process p[n];

    for (int i = 0; i < n; i++) {
        printf("Process %d\n", i + 1);
        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].arrivalTime);
        printf("Enter Burst Time: ");
        scanf("%d", &p[i].burstTime);
        p[i].processId = i + 1;
        p[i].remainingTime = p[i].burstTime;  
        p[i].flag = 0;
        p[i].responseTime = -1;  
        printf("\n");
    }

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    // Sort processes based on arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrivalTime > p[j + 1].arrivalTime) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    roundRobinScheduling(p, n, quantum);
    return 0;
}

void roundRobinScheduling(Process p[], int n, int quantum) {
    int totalWaitingTime = 0, totalTurnAroundTime = 0, totalResponseTime = 0;
    float avgWaitingTime = 0, avgTurnAroundTime = 0, avgResponseTime = 0;
    int remainingProcesses = n, exec;
    int elapsedTime = p[0].arrivalTime;

    // Queue initialization
    int waitQueue[15], front = 0, rear = 0;
    waitQueue[rear++] = 0;
    p[0].flag = 1;

    // Round Robin Scheduling
    printf("\nGantt Chart:\n\n");
    while (remainingProcesses) {
        exec = waitQueue[front++];
        
        if (p[exec].responseTime == -1) {
            p[exec].responseTime = elapsedTime - p[exec].arrivalTime;
        }

        if (p[exec].remainingTime > quantum) {
            p[exec].remainingTime -= quantum;
            elapsedTime += quantum;
            printf("|(%d) P%d (%d)", elapsedTime - quantum, p[exec].processId, elapsedTime);
        } else {
            elapsedTime += p[exec].remainingTime;
            printf("|(%d) P%d (%d)", elapsedTime - p[exec].remainingTime, p[exec].processId, elapsedTime);
            p[exec].remainingTime = 0;
            p[exec].completionTime = elapsedTime;
            p[exec].turnAroundTime = p[exec].completionTime - p[exec].arrivalTime;
            p[exec].waitingTime = p[exec].turnAroundTime - p[exec].burstTime;
            totalTurnAroundTime += p[exec].turnAroundTime;
            totalWaitingTime += p[exec].waitingTime;
            totalResponseTime += p[exec].responseTime;
            remainingProcesses--;
        }

        // Add new processes to the queue
        for (int i = 0; i < n && p[i].arrivalTime <= elapsedTime; i++) {
            if (p[i].flag == 0 && p[i].remainingTime > 0) {
                waitQueue[rear++] = i;
                p[i].flag = 1;
            }
        }

        // Re-queue the current process if it's not finished
        if (p[exec].remainingTime > 0) {
            waitQueue[rear++] = exec;
        }
    }

    avgTurnAroundTime = (float)totalTurnAroundTime / n;
    avgWaitingTime = (float)totalWaitingTime / n;
    avgResponseTime = (float)totalResponseTime / n;

    
    printf("|\nObservation Table\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].processId, p[i].arrivalTime, p[i].burstTime, p[i].completionTime, p[i].turnAroundTime, p[i].waitingTime, p[i].responseTime);
    }

    printf("\nAverage TAT = %.2f\nAverage WT = %.2f\nAverage RT = %.2f\n", avgTurnAroundTime, avgWaitingTime, avgResponseTime);
}
