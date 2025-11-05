#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int *pages;
int n, framesCount;
int fifo_faults = 0, lru_faults = 0;

// ---------- LRU Helper ----------
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

// ---------- LRU THREAD ----------
void *lru_thread(void *arg) {
    long tid = (long)arg;
    int *frames = (int *)malloc(framesCount * sizeof(int));
    int *time = (int *)malloc(framesCount * sizeof(int));
    int counter = 0, pageFaults = 0;
    int i, j, pos, flag1, flag2;

    for (i = 0; i < framesCount; i++)
        frames[i] = -1;

    printf("\n[Thread %ld] --- LRU Page Replacement ---\n", tid);
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

    printf("[Thread %ld] Total Page Faults (LRU): %d\n", tid, pageFaults);
    lru_faults = pageFaults;
    free(frames);
    free(time);
    pthread_exit(NULL);
}

// ---------- FIFO THREAD ----------
void *fifo_thread(void *arg) {
    long tid = (long)arg;
    int *frames = (int *)malloc(framesCount * sizeof(int));
    int i, j, k = 0, flag, pageFaults = 0;

    for (i = 0; i < framesCount; i++)
        frames[i] = -1;

    printf("\n[Thread %ld] --- FIFO Page Replacement ---\n", tid);
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

    printf("[Thread %ld] Total Page Faults (FIFO): %d\n", tid, pageFaults);
    fifo_faults = pageFaults;
    free(frames);
    pthread_exit(NULL);
}

// ---------- MAIN ----------
int main() {
    printf("Enter number of pages: ");
    scanf("%d", &n);

    pages = (int *)malloc(n * sizeof(int));
    printf("Enter the page reference string: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &framesCount);

    pthread_t tid1, tid2;

    // Create threads for FIFO and LRU
    pthread_create(&tid1, NULL, fifo_thread, (void *)1);
    pthread_create(&tid2, NULL, lru_thread, (void *)2);

    // Wait for both threads to complete
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    // Calculate average page faults
    float avg = (fifo_faults + lru_faults) / 2.0;
    printf("\n---------------------------------\n");
    printf("FIFO Faults = %d\n", fifo_faults);
    printf("LRU  Faults = %d\n", lru_faults);
    printf("Average Page Faults = %.2f\n", avg);
    printf("---------------------------------\n");

    free(pages);
    return 0;
}
