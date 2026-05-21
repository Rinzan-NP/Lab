#include <stdio.h>

int main() {

    int pages[50];
    int frames[10];

    int n=10; // total pages
    int f=3; // total frames

    int i, j;

    // FIFO replacement pointer
    int next = 0;
    int found;

    int faults = 0;


    printf("Enter page reference string:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    // -1 means empty frame
    for(i = 0; i < f; i++) {
        frames[i] = -1;
    }

    for(i = 0; i < n; i++) {
        found = 0;

        for(j = 0; j < f; j++) {

            if(frames[j] == pages[i]) {
                found = 1; //hit
                break;
            }
        }

      
        if(!found) {
            // Replace oldest page
            frames[next] = pages[i];
            next = (next + 1) % f;
            faults++;
        }
        printf("%d\t", pages[i]);

        for(j = 0; j < f; j++) {
            if(frames[j] == -1)
                printf("-\t");
            else
                printf("%d\t", frames[j]);
        }

        if(found)
            printf("Hit\n");
        else
            printf("Fault\n");
    }

    printf("\nTotal Page Faults = %d\n",faults);
    return 0;
}