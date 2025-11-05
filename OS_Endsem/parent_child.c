#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

void sstf(int requests[], int n, int head) {
    int visited[n], total = 0, count = 0;
    for (int i = 0; i < n; i++) visited[i] = 0;

    printf("\nChild Process: Running SSTF Scheduling\n");
    while (count < n) {
        int min = 10000, idx = -1;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                int diff = abs(head - requests[i]);
                if (diff < min) {
                    min = diff;
                    idx = i;
                }
            }
        }
        visited[idx] = 1;
        total += min;
        head = requests[idx];
        count++;
        printf(" -> %d", head);
    }
    printf("\nTotal Seek Time (SSTF): %d\n", total);
}

void scan(int requests[], int n, int head, int direction, int disk_size) {
    printf("\nParent Process: Running SCAN Scheduling\n");
    int total = 0, i, j, temp;

    // Sort requests
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    int pos = 0;
    while (pos < n && head > requests[pos]) pos++;

    if (direction == 1) { // right
        for (i = pos; i < n; i++) {
            printf(" -> %d", requests[i]);
            total += abs(head - requests[i]);
            head = requests[i];
        }
        total += abs(disk_size - 1 - head);
        head = disk_size - 1;
        for (i = pos - 1; i >= 0; i--) {
            printf(" -> %d", requests[i]);
            total += abs(head - requests[i]);
            head = requests[i];
        }
    } else { // left
        for (i = pos - 1; i >= 0; i--) {
            printf(" -> %d", requests[i]);
            total += abs(head - requests[i]);
            head = requests[i];
        }
        total += head; // move to 0
        head = 0;
        for (i = pos; i < n; i++) {
            printf(" -> %d", requests[i]);
            total += abs(head - requests[i]);
            head = requests[i];
        }
    }
    printf("\nTotal Seek Time (SCAN): %d\n", total);
}

int main() {
    int n, head, i, disk_size, direction;
    printf("Enter number of requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter request sequence: ");
    for (i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &disk_size);

    printf("Enter direction (1 for right, 0 for left): ");
    scanf("%d", &direction);

    pid_t pid = fork();

    if (pid == 0) {
        // Child process → run SSTF
        sstf(requests, n, head);
        exit(0);
    } else {
        // Parent process waits for child
        wait(NULL);
        // Then runs SCAN
        scan(requests, n, head, direction, disk_size);
    }

    return 0;
}
