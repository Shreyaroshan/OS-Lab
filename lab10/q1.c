#include <stdio.h>
#include <stdlib.h>

void fifo(int pages[], int n, int framesCount) {
    int *frames = (int *)malloc(framesCount * sizeof(int));
    int i, j, k = 0, flag, pageFaults = 0;

    for (i = 0; i < framesCount; i++)
        frames[i] = -1;

    printf("\n--- FIFO Page Replacement ---\n");
    printf("Page\tFrames\n");

    for (i = 0; i < n; i++) {
        flag = 0;
        for (j = 0; j < framesCount; j++) {
            if (frames[j] == pages[i]) {
                flag = 1;
                break;
            }
        }

        if (flag == 0) {
            frames[k] = pages[i];
            k = (k + 1) % framesCount;
            pageFaults++;
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

    printf("Total Page Faults (FIFO): %d\n", pageFaults);
    free(frames);
}

int predict(int pages[], int frames[], int n, int index, int framesCount) {
    int res = -1, farthest = index, i, j;
    for (i = 0; i < framesCount; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == n)
            return i;
    }
    return (res == -1) ? 0 : res;
}

void optimal(int pages[], int n, int framesCount) {
    int *frames = (int *)malloc(framesCount * sizeof(int));
    int i, j, pageFaults = 0, filled = 0;

    for (i = 0; i < framesCount; i++)
        frames[i] = -1;

    printf("\n--- Optimal Page Replacement ---\n");
    printf("Page\tFrames\n");

    for (i = 0; i < n; i++) {
        int flag = 0;
        for (j = 0; j < framesCount; j++) {
            if (frames[j] == pages[i]) {
                flag = 1;
                break;
            }
        }

        if (!flag) {
            if (filled < framesCount)
                frames[filled++] = pages[i];
            else {
                int pos = predict(pages, frames, n, i + 1, framesCount);
                frames[pos] = pages[i];
            }
            pageFaults++;
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

    printf("Total Page Faults (Optimal): %d\n", pageFaults);
    free(frames);
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

    fifo(pages, n, framesCount);
    optimal(pages, n, framesCount);

    free(pages);
    return 0;
}
