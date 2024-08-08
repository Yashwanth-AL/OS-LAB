// 8.b) Implement FCFS scheduling algorithm by defining the process structure. 

#include <stdio.h>

typedef struct node {
    int processId;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;
    int responseTime;
} Process;

void fcfs(Process[], int);

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
        printf("\n");
    }

    // Sort processes based on arrival time (if needed)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrivalTime > p[j + 1].arrivalTime) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    fcfs(p, n);
    return 0;
}

void fcfs(Process p[], int n) {
    int elapsedTime = 0;
    float avgWaitingTime = 0;
    float avgTurnAroundTime = 0;
    float avgResponseTime = 0;
    int totalWaitingTime = 0;
    int totalTurnAroundTime = 0;
    int totalResponseTime = 0;

    printf("\nGantt chart\n");
    for (int i = 0; i < n; i++) {
        if (p[i].arrivalTime > elapsedTime) // to take care of the idle time
            elapsedTime = elapsedTime + (p[i].arrivalTime - elapsedTime);
        
        int temp = elapsedTime;
        p[i].responseTime = elapsedTime - p[i].arrivalTime;
        elapsedTime += p[i].burstTime;
        p[i].completionTime = elapsedTime;
        p[i].turnAroundTime = p[i].completionTime - p[i].arrivalTime;
        p[i].waitingTime = p[i].turnAroundTime - p[i].burstTime;
        printf("|%d<---P%d--->%d", temp, p[i].processId, elapsedTime);
    }

    printf("|\n");
    printf("Observation Table\nPID \tAT \t BT \tCT \tTT \tWT \tRT \n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].processId, p[i].arrivalTime,
               p[i].burstTime, p[i].completionTime, p[i].turnAroundTime, p[i].waitingTime, p[i].responseTime);
        
        totalTurnAroundTime += p[i].turnAroundTime;
        totalWaitingTime += p[i].waitingTime;
        totalResponseTime += p[i].responseTime;
    }

    avgTurnAroundTime = (float)totalTurnAroundTime / n;
    avgWaitingTime = (float)totalWaitingTime / n;
    avgResponseTime = (float)totalResponseTime / n;

    printf("\nAverage Waiting Time: %.2lf\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2lf\n", avgTurnAroundTime);
    printf("Average Response Time: %.2lf\n", avgResponseTime);
}
