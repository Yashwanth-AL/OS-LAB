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
    int priority;
    int remainingTime;
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
        p[i].remainingTime = p[i].burstTime;  // creating copy of burst time
        printf("\n");
    }
    
    priorityScheduling(p, n);
    return 0;
}

void priorityScheduling(Process p[], int n) {
    int time[100], process[100], j = -1, k = -1;
    int totalWaitingTime = 0;
    int totalTurnAroundTime = 0;
    int totalResponseTime = 0;
    float avgWaitingTime = 0;
    float avgTurnAroundTime = 0;
    float avgResponseTime = 0;
    int elapsedTime = 0;
    int remainingProcesses = n;

    time[++j] = 0;  

    printf("\nGantt Chart:\n\n");

    while (remainingProcesses) {
        int exec = -1;
        int minPriority = 9999;

        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= elapsedTime && p[i].remainingTime > 0) {
                if (p[i].priority < minPriority || 
                    (p[i].priority == minPriority && p[i].arrivalTime < p[exec].arrivalTime)) {
                    minPriority = p[i].priority;
                    exec = i;
                }
            }
        }

        if (exec == -1) {
            process[++k] = 0;  
            elapsedTime++;
            time[++j] = elapsedTime;
            printf("|(%d) IDLE (%d)", time[j-1], time[j]);
        } else {
            if (p[exec].remainingTime == p[exec].burstTime) { 
                p[exec].responseTime = elapsedTime - p[exec].arrivalTime;
            }
            p[exec].remainingTime--;
            process[++k] = p[exec].processId;
            elapsedTime++;
            time[++j] = elapsedTime;

            if (p[exec].remainingTime == 0) {
                p[exec].completionTime = elapsedTime;
                p[exec].turnAroundTime = p[exec].completionTime - p[exec].arrivalTime;
                p[exec].waitingTime = p[exec].turnAroundTime - p[exec].burstTime;
                totalTurnAroundTime += p[exec].turnAroundTime;
                totalWaitingTime += p[exec].waitingTime;
                totalResponseTime += p[exec].responseTime;
                remainingProcesses--;
            }
            printf("|(%d) P%d (%d)", time[j-1], p[exec].processId, time[j]);
        }
    }

    printf("|\n");

    avgTurnAroundTime = (float)totalTurnAroundTime / n;
    avgWaitingTime = (float)totalWaitingTime / n;
    avgResponseTime = (float)totalResponseTime / n;

    // Print the process table with details
     printf("Observation Table\nPID \tAT \tBT \tCT \tTT \tWT \tRT\tPR\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].processId, p[i].arrivalTime, p[i].burstTime, p[i].completionTime, p[i].turnAroundTime, p[i].waitingTime, p[i].responseTime, p[i].priority);
    }

    printf("\nGantt Chart\t(P0-->idle time)\n");
    for (int i = 0; i <= k; i++)
        printf("| P%d\t", process[i]);

    printf("|\n");

    for (int i = 0; i <= j; i++)
        printf("%d\t", time[i]);

    printf("\n");

    printf("\nAverage TAT = %.2f\nAverage WT = %.2f\nAverage RT = %.2f\n", avgTurnAroundTime, avgWaitingTime, avgResponseTime);
}
