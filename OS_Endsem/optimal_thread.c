#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int *pages = NULL;
int n = 0, framesCount = 0;
int faults_small = 0, faults_large = 0;

// ---------- Optimal Page Replacement Function ----------
int predict(int pages[], int frames[], int n, int index, int frameCount) {
    int res = -1, farthest = index;
    for (int i = 0; i < frameCount; i++) {
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

int optimal(int pages[], int n, int frameCount, long tid) {
    int *frames = (int *)malloc(frameCount * sizeof(int));
    int pageFaults = 0, filled = 0;

    printf("\n[Thread %ld] --- Optimal Page Replacement (%d frames) ---\n", tid, frameCount);
    printf("Page\tFrames\n");

    for (int i = 0; i < frameCount; i++)
        frames[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0;

        // Check if page already exists in frames
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            // If empty space available
            if (filled < frameCount) {
                frames[filled++] = pages[i];
            } else {
                int pos = predict(pages, frames, n, i + 1, frameCount);
                frames[pos] = pages[i];
            }
            pageFaults++;
        }

        // Print current frame contents
        printf("%d\t", pages[i]);
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("[Thread %ld] Total Page Faults: %d\n", tid, pageFaults);
    free(frames);
    return pageFaults;
}

// ---------- Thread 1: Input ----------
void *input_thread(void *arg) {
    long tid = (long)arg;
    printf("\n[Thread %ld] Enter number of pages: ", tid);
    scanf("%d", &n);

    pages = (int *)malloc(n * sizeof(int));
    printf("[Thread %ld] Enter page reference string: ", tid);
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("[Thread %ld] Enter number of frames: ", tid);
    scanf("%d", &framesCount);

    pthread_exit(NULL);
}

// ---------- Thread 2: Optimal with given frames ----------
void *optimal_small_thread(void *arg) {
    long tid = (long)arg;
    faults_small = optimal(pages, n, framesCount, tid);
    pthread_exit(NULL);
}

// ---------- Thread 3: Optimal with larger frames ----------
void *optimal_large_thread(void *arg) {
    long tid = (long)arg;
    int largerFrames = framesCount + 2;
    faults_large = optimal(pages, n, largerFrames, tid);
    pthread_exit(NULL);
}

// ---------- MAIN ----------
int main() {
    pthread_t t1, t2, t3;

    // Create input thread
    pthread_create(&t1, NULL, input_thread, (void *)1);
    pthread_join(t1, NULL);

    // Create threads for Optimal algorithms
    pthread_create(&t2, NULL, optimal_small_thread, (void *)2);
    pthread_create(&t3, NULL, optimal_large_thread, (void *)3);

    // Wait for both optimal threads to finish
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    // Calculate and show average page faults
    float avg = (faults_small + faults_large) / 2.0;
    printf("\n---------------------------------\n");
    printf("Optimal (small) Page Faults = %d\n", faults_small);
    printf("Optimal (large) Page Faults = %d\n", faults_large);
    printf("Average Page Faults = %.2f\n", avg);
    printf("---------------------------------\n");

    free(pages);
    return 0;
}
