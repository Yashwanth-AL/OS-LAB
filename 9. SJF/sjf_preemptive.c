#include <stdio.h>

typedef struct process {
    int processId;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;
    int responseTime;
} Process;

void sjfPreemptive(Process[], int);

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
        p[i].remainingTime = p[i].burstTime; // creating copy of burst time
        printf("\n");
    }
    sjfPreemptive(p, n);
    return 0;
}

void sjfPreemptive(Process p[], int n) {
    int timeProgress[100], processTrack[100], j = -1, k = -1;
    float avgWaitingTime = 0;
    float avgTurnAroundTime = 0;
    float avgResponseTime = 0;
    int totalWaitingTime = 0;
    int totalTurnAroundTime = 0;
    int totalResponseTime = 0;
    int elapsedTime = 0;
    int remainingProcesses = n;
    timeProgress[++j] = 0;

    while (remainingProcesses) {
        int exec = -1; // 'exec' will store the index of the process that'll be selected
        int shortestBurstTime = 9999;
        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= elapsedTime && p[i].remainingTime > 0) {
                if (p[i].remainingTime < shortestBurstTime) {
                    shortestBurstTime = p[i].remainingTime;
                    exec = i;
                }
            }
        }
        if (exec == -1) {
            processTrack[++k] = 0;
            elapsedTime++;
            timeProgress[++j] = elapsedTime;
            continue;
        }
        if (p[exec].remainingTime == p[exec].burstTime) { // first cpu allocation
            p[exec].responseTime = elapsedTime - p[exec].arrivalTime;
        }
        p[exec].remainingTime--;
        elapsedTime++;

        processTrack[++k] = p[exec].processId;
        timeProgress[++j] = elapsedTime;
        if (p[exec].remainingTime == 0) { // process has been executed
            p[exec].completionTime = elapsedTime;
            p[exec].turnAroundTime = p[exec].completionTime - p[exec].arrivalTime;
            p[exec].waitingTime = p[exec].turnAroundTime - p[exec].burstTime;
            totalTurnAroundTime += p[exec].turnAroundTime;
            totalWaitingTime += p[exec].waitingTime;
            totalResponseTime += p[exec].responseTime;
            remainingProcesses--;
        }
    }

    avgTurnAroundTime = (float)totalTurnAroundTime / n;
    avgWaitingTime = (float)totalWaitingTime / n;
    avgResponseTime = (float)totalResponseTime / n;
    
    printf("Observation Table\nPID \tAT \tBT \tCT \tTT \tWT \tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].processId, 
               p[i].arrivalTime, p[i].burstTime, 
               p[i].completionTime, p[i].turnAroundTime, 
               p[i].waitingTime, p[i].responseTime);
    }

    printf("\nGantt Chart\n(P0-->idle time)\n");
    for (int i = 0; i <= k; i++)
        printf("| P%d\t", processTrack[i]);

    printf("|\n");

    for (int i = 0; i <= j; i++)
        printf("%d\t", timeProgress[i]);

    printf("\n");
    printf("\nAverage Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnAroundTime);
    printf("Average Response Time: %.2f\n", avgResponseTime);
}
