#include <stdio.h>

struct process {

    int pid;   // Process ID
    int at;    // Arrival Time
    int bt;    // Burst Time
    int rt;    // Remaining Time

    int ct;    // Completion Time
    int wt;    // Waiting Time
    int tat;   // Turnaround Time
};

int main() {

    int n, i;

    int tq = 3; // Time Quantum

    int queue[100];

    int front = 0;
    int rear = 0;

    int tm = 0; // Current Time

    int completed = 0;

    printf("Enter number of processes : ");
    scanf("%d", &n);

    struct process p[n];

    // Tracks whether process already entered queue
    int inQueue[n];

    // Initialize inQueue to 0
    for(i = 0; i < n; i++) {
        inQueue[i] = 0;
    }

    // ===== INPUT =====

    for(i = 0; i < n; i++) {

        printf("\nEnter pid, arrival time, burst time : ");

        scanf("%d", &p[i].pid);
        scanf("%d", &p[i].at);
        scanf("%d", &p[i].bt);

        // Initially Remaining Time = Burst Time
        p[i].rt = p[i].bt;
    }

    // ===== ADD INITIAL PROCESSES =====
    // Add all processes arriving at time 0

    for(i = 0; i < n; i++) {

        if(p[i].at == 0) {

            queue[rear++] = i;

            inQueue[i] = 1;
        }
    }

    // ===== ROUND ROBIN =====

    while(completed != n) {

        // ===== CPU IDLE =====

        if(front == rear) {

            // No process ready
            // Increase time

            tm++;

            // Check newly arrived processes

            for(i = 0; i < n; i++) {

                if(p[i].at == tm &&
                   !inQueue[i]) {

                    queue[rear++] = i;

                    inQueue[i] = 1;
                }
            }

            // Skip execution part
            continue;
        }

        // ===== TAKE PROCESS FROM QUEUE =====

        int idx = queue[front++];

        // ===== EXECUTION TIME =====

        // Execute minimum of:
        // remaining time OR time quantum

        int exec =
            p[idx].rt > tq ? tq : p[idx].rt;

        // Increase current time

        tm += exec;

        // Reduce remaining time

        p[idx].rt -= exec;

        // ===== ADD NEWLY ARRIVED PROCESSES =====

        for(i = 0; i < n; i++) {

            if(p[i].at <= tm &&
               !inQueue[i]) {

                queue[rear++] = i;

                inQueue[i] = 1;
            }
        }

        // ===== CHECK PROCESS STATUS =====

        // Process completed

        if(p[idx].rt == 0) {

            p[idx].ct = tm;

            completed++;
        }

        // Process unfinished
        // Reinsert into queue

        else {

            queue[rear++] = idx;
        }
    }

    // ===== CALCULATE WT & TAT =====

    float totalWT = 0;
    float totalTAT = 0;

    printf("\n\nRound Robin Result\n");

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(i = 0; i < n; i++) {

        // Turnaround Time

        p[i].tat =
            p[i].ct - p[i].at;

        // Waiting Time

        p[i].wt =
            p[i].tat - p[i].bt;

        totalWT += p[i].wt;

        totalTAT += p[i].tat;

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].ct,
               p[i].tat,
               p[i].wt);
    }

    // ===== AVERAGES =====

    printf("\nAverage Waiting Time = %.2f",
           totalWT / n);

    printf("\nAverage Turnaround Time = %.2f\n",
           totalTAT / n);

    return 0;
}