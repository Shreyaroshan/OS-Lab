#include <stdio.h>
#include <stdlib.h>

int findLRU(int *time, int framesCount) {
    int i, minimum = time[0], pos = 0;
    for (i = 1; i < framesCount; i++) {
        if (time[i] < minimum) {
            minimum = time[i];
            pos = i;
        }
    }
    return pos;
}

void lru(int pages[], int n, int framesCount) {
    int *frames = (int *)malloc(framesCount * sizeof(int));
    int *time = (int *)malloc(framesCount * sizeof(int));
    int counter = 0, pageFaults = 0;
    int i, j, pos, flag1, flag2;

    for (i = 0; i < framesCount; i++)
        frames[i] = -1;

    printf("\n--- LRU Page Replacement ---\n");
    printf("Page\tFrames\n");

    for (i = 0; i < n; i++) {
        flag1 = flag2 = 0;

        for (j = 0; j < framesCount; j++) {
            if (frames[j] == pages[i]) {
                counter++;
                time[j] = counter;
                flag1 = flag2 = 1;
                break;
            }
        }

        if (flag1 == 0) {
            for (j = 0; j < framesCount; j++) {
                if (frames[j] == -1) {
                    counter++;
                    pageFaults++;
                    frames[j] = pages[i];
                    time[j] = counter;
                    flag2 = 1;
                    break;
                }
            }
        }

        if (flag2 == 0) {
            pos = findLRU(time, framesCount);
            counter++;
            pageFaults++;
            frames[pos] = pages[i];
            time[pos] = counter;
        }

        printf("%d\t", pages[i]);
        for (j = 0; j < framesCount; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("Total Page Faults (LRU): %d\n", pageFaults);
    free(frames);
    free(time);
}

int main() {
    int n, framesCount, i;
    printf("Enter number of pages: ");
    scanf("%d", &n);

    int *pages = (int *)malloc(n * sizeof(int));
    printf("Enter the page reference string: ");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &framesCount);

    lru(pages, n, framesCount);

    free(pages);
    return 0;
}
