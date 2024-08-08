#include <stdio.h>

typedef struct process {
    int processId;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;
    int finished;
    int responseTime;
} Process;

void sjfNP(Process[], int);

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
        p[i].processId = i + 1;
        p[i].finished = 0;
        printf("\n");
    }
    sjfNP(p, n);
    return 0;
}

void sjfNP(Process p[], int n) {
    float avgWaitingTime = 0;
    float avgTurnAroundTime = 0;
    float avgResponseTime = 0;
    int totalWaitingTime = 0;
    int totalTurnAroundTime = 0;
    int totalResponseTime = 0;
    int elapsedTime = 0;
    int remainingProcesses = n;
    int exec;

    printf("\nGantt chart\n");
    while (remainingProcesses) {
        // Find the highest priority process that has arrived and not finished
        exec = -1;
        int shortestBurstTime = 9999;
        for (int i = 0; i < n; i++) {
            if (p[i].finished == 0 && p[i].arrivalTime <= elapsedTime) {
                if (p[i].burstTime < shortestBurstTime) {
                    exec = i;
                    shortestBurstTime = p[i].burstTime;
                }
            }
        }
        if (exec == -1) {
            // No process available to execute, increment the elapsed time
            printf("|(%d)***(%d)", elapsedTime, elapsedTime + 1);
            elapsedTime++;
        } else {
            // Execute the selected process
            int temp = elapsedTime;
            p[exec].responseTime = elapsedTime - p[exec].arrivalTime;
            elapsedTime += p[exec].burstTime;
            p[exec].completionTime = elapsedTime;
            p[exec].turnAroundTime = p[exec].completionTime - p[exec].arrivalTime;
            p[exec].waitingTime = p[exec].turnAroundTime - p[exec].burstTime;
            printf("|(%d) P%d (%d)", temp, p[exec].processId, elapsedTime);
            remainingProcesses--;
            p[exec].finished = 1;
        }
    }
    printf("\nPID \tAT \tBT \tCT \tTT \tWT \tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].processId, 
               p[i].arrivalTime, p[i].burstTime, 
               p[i].completionTime, p[i].turnAroundTime, 
               p[i].waitingTime, p[i].responseTime);

        totalTurnAroundTime += p[i].turnAroundTime;
        totalWaitingTime += p[i].waitingTime;
        totalResponseTime += p[i].responseTime;
    }

    avgTurnAroundTime = (float)totalTurnAroundTime / n;
    avgWaitingTime = (float)totalWaitingTime / n;
    avgResponseTime = (float)totalResponseTime / n;

    printf("\nAverage Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnAroundTime);
    printf("Average Response Time: %.2f\n", avgResponseTime);
}
