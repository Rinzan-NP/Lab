#include <stdio.h>

// Structure to store process details

struct Process {

    int pid;        // Process ID
    int at;         // Arrival Time
    int bt;         // Burst Time
    int priority;   // Priority

    int ct;         // Completion Time
    int tat;        // Turnaround Time
    int wt;         // Waiting Time

    int completed;  // 0 = not completed
                    // 1 = completed
};

int main() {

    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // ===== INPUT =====

    for(int i = 0; i < n; i++) {

        // Assign process ID

        p[i].pid = i + 1;

        printf("\nEnter Arrival Time for P%d: ",
               i + 1);
        scanf("%d", &p[i].at);

        printf("Enter Burst Time for P%d: ",
               i + 1);
        scanf("%d", &p[i].bt);

        printf("Enter Priority for P%d: ",
               i + 1);
        scanf("%d", &p[i].priority);

        // Initially process is not completed

        p[i].completed = 0;
    }

    // ===== VARIABLES =====

    int completed = 0; // completed process count

    int time = 0;      // current CPU time

    float totalWT = 0;

    // ===== SCHEDULING =====

    while(completed != n) {

        int idx = -1;

        // Stores highest priority found

        int bestPriority = -1;

        // ===== FIND BEST PROCESS =====

        for(int i = 0; i < n; i++) {

            // Process should:
            // 1. not be completed
            // 2. already arrived

            if(!p[i].completed &&
               p[i].at <= time) {

                // Higher number = higher priority

                if(p[i].priority >
                   bestPriority) {

                    bestPriority =
                        p[i].priority;

                    idx = i;
                }
            }
        }

        // ===== CPU IDLE =====

        // No process available currently

        if(idx == -1) {

            time++;

            continue;
        }

        // ===== EXECUTE PROCESS =====

        // Non-preemptive:
        // process runs fully once selected

        time += p[idx].bt;

        // Completion Time

        p[idx].ct = time;

        // Turnaround Time

        p[idx].tat =
            p[idx].ct - p[idx].at;

        // Waiting Time

        p[idx].wt =
            p[idx].tat - p[idx].bt;

        // Mark process completed

        p[idx].completed = 1;

        completed++;

        totalWT += p[idx].wt;
    }

    // ===== OUTPUT =====

    printf("\nNon-Preemptive Priority Scheduling Result:\n");

    printf("PID\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++) {

        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",

               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].priority,
               p[i].ct,
               p[i].tat,
               p[i].wt);
    }

    // ===== AVERAGE WAITING TIME =====

    printf("\nAverage Waiting Time = %.2f\n",
           totalWT / n);

    return 0;
}