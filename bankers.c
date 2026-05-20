#include <stdio.h>

int main() {
    int n = 5; // Processes
    int m = 3; // Resource types

    int alloc[5][3] = {

        {0,1,0},
        {2,0,0},
        {3,0,2},
        {2,1,1},
        {0,0,2}
    };

    int max[5][3] = {

        {7,5,3},
        {3,2,2},
        {9,0,2},
        {2,2,2},
        {4,3,3}
    };

    int avail[3] = {3,3,2};
    int need[5][3];
    int finish[5] = {0};
    int safeSeq[5];

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            need[i][j] =
                max[i][j] - alloc[i][j];
        }
    }
    int count = 0;

    // ===== SAFETY ALGORITHM =====

    while(count < n) {

        int found = 0;

        // Search executable process

        for(int i = 0; i < n; i++) {

            // Process should not finish already

            if(!finish[i]) {

                int j;

                // Check whether process needs
                // are less than available resources

                for(j = 0; j < m; j++) {

                    if(need[i][j] > avail[j]) {

                        break;
                    }
                }

                // If loop completed fully
                // process can execute safely

                if(j == m) {

                    // Release allocated resources

                    for(int k = 0; k < m; k++) {

                        avail[k] += alloc[i][k];
                    }

                    // Add process to safe sequence

                    safeSeq[count++] = i;

                    // Mark process completed

                    finish[i] = 1;

                    found = 1;
                }
            }
        }

        // No safe process found

        if(!found) {

            printf("System is in UNSAFE state\n");

            return 0;
        }
    }

    // ===== OUTPUT =====

    printf("System is in SAFE state\n");

    printf("Safe Sequence : ");

    for(int i = 0; i < n; i++) {

        printf("P%d ", safeSeq[i]);
    }

    // ===== FINAL AVAILABLE RESOURCES =====

    printf("\n\nFinal Available Resources : ");

    for(int i = 0; i < m; i++) {

        printf("%d ", avail[i]);
    }
    printf("\n");
    return 0;
}