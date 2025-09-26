#include <stdio.h>
#include <stdbool.h>

#define P 5   // Number of processes
#define R 3   // Number of resources

// Function to check if system is in safe state
bool isSafe(int processes[], int avail[], int max[][R], int allot[][R]) {
    int work[R];
    bool finish[P] = {0};
    int safeSeq[P];
    int count = 0;

    // Initialize work as available
    for (int i = 0; i < R; i++)
        work[i] = avail[i];

    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < R; j++)
                    if (max[p][j] - allot[p][j] > work[j])
                        break;

                if (j == R) {
                    for (int k = 0; k < R; k++)
                        work[k] += allot[p][k];

                    safeSeq[count++] = p;
                    finish[p] = 1;
                    found = true;
                }
            }
        }
        if (!found) {
            printf("System is NOT in a safe state!\n");
            return false;
        }
    }

    printf("System is in a safe state.\nSafe sequence: ");
    for (int i = 0; i < P; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");

    return true;
}

// Resource Request Algorithm
void requestResources(int processes[], int avail[], int max[][R], int allot[][R],
                      int reqProcess, int request[]) {
    printf("\nProcess P%d requesting resources: ", reqProcess);
    for (int i = 0; i < R; i++)
        printf("%d ", request[i]);
    printf("\n");

    // Check if request <= need
    for (int i = 0; i < R; i++) {
        if (request[i] > max[reqProcess][i] - allot[reqProcess][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return;
        }
    }

    // Check if request <= available
    for (int i = 0; i < R; i++) {
        if (request[i] > avail[i]) {
            printf("Process must wait: resources not available.\n");
            return;
        }
    }

    // Pretend to allocate resources
    for (int i = 0; i < R; i++) {
        avail[i] -= request[i];
        allot[reqProcess][i] += request[i];
    }

    // Check if system is still safe
    if (isSafe(processes, avail, max, allot)) {
        printf("Request can be granted safely.\n");
    } else {
        // Rollback
        for (int i = 0; i < R; i++) {
            avail[i] += request[i];
            allot[reqProcess][i] -= request[i];
        }
        printf("Request cannot be granted (unsafe state).\n");
    }
}

int main() {
    int processes[P] = {0, 1, 2, 3, 4};

    int avail[R] = {3, 3, 2}; // Available instances

    int max[P][R] = { {7, 5, 3},
                      {3, 2, 2},
                      {9, 0, 2},
                      {2, 2, 2},
                      {4, 3, 3} };

    int allot[P][R] = { {0, 1, 0},
                        {2, 0, 0},
                        {3, 0, 2},
                        {2, 1, 1},
                        {0, 0, 2} };

    // Check initial state
    isSafe(processes, avail, max, allot);

    // Example: Process 1 requests {1, 0, 2}
    int request1[R] = {1, 0, 2};
    requestResources(processes, avail, max, allot, 1, request1);

    return 0;
}
