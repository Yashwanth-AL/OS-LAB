#include <stdio.h>
#include <stdlib.h>

typedef struct process {
    int processId;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;
    int finished;
    int priority;
} Process;

void priorityScheduling(Process[], int);

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process p[n];
    
    // Accept process details from the user
    for (int i = 0; i < n; i++) {
        printf("Process %d\n", i + 1);
        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].arrivalTime);
        printf("Enter Burst Time: ");
        scanf("%d", &p[i].burstTime);
        printf("Enter Priority: ");
        scanf("%d", &p[i].priority);
        p[i].processId = i + 1;
        p[i].finished = 0;
        printf("\n");
    }
    
    priorityScheduling(p, n);
    return 0;
}

void priorityScheduling(Process p[], int n) {
    int totalWaitingTime = 0;
    int totalTurnAroundTime = 0;
    float avgWaitingTime = 0;
    float avgTurnAroundTime = 0;
    int remainingProcesses = n;
    int elapsedTime = 0;
    int exec; 

    printf("\nGantt Chart:\n\n");

    while (remainingProcesses) {
        exec = -1;
        int minPriority = 9999;

        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= elapsedTime && p[i].finished == 0) {
                if (p[i].priority < minPriority || 
                    (p[i].priority == minPriority && p[i].arrivalTime < p[exec].arrivalTime)) {
                    minPriority = p[i].priority;
                    exec = i;
                }
            }
        }

        if (exec == -1) {
            printf("|(%d)***(%d)", elapsedTime, elapsedTime + 1);
            elapsedTime++;
        } else {
            int temp = elapsedTime;
            elapsedTime += p[exec].burstTime;
            p[exec].completionTime = elapsedTime;
            p[exec].turnAroundTime = p[exec].completionTime - p[exec].arrivalTime;
            p[exec].waitingTime = p[exec].turnAroundTime - p[exec].burstTime;
            totalTurnAroundTime += p[exec].turnAroundTime;
            totalWaitingTime += p[exec].waitingTime;
            printf("|(%d) P%d (%d)", temp, p[exec].processId, elapsedTime);
            p[exec].finished = 1;
            remainingProcesses--;
        }
    }

    printf("|\n");

    avgTurnAroundTime = (float)totalTurnAroundTime / n;
    avgWaitingTime = (float)totalWaitingTime / n;

    // Print the process table with details
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tP\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].processId, p[i].arrivalTime, p[i].burstTime, p[i].completionTime, p[i].turnAroundTime, p[i].waitingTime, p[i].priority);
    }

    printf("\nAverage TAT = %.2f\nAverage WT = %.2f\n", avgTurnAroundTime, avgWaitingTime);
}
