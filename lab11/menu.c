#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// ============ SSTF (Shortest Seek Time First) ============
void SSTF(int req[], int n, int head) {
    int done[100] = {0}, count = 0, total = 0;
    printf("\nSSTF Disk Scheduling Order: %d", head);

    while (count < n) {
        int min = 9999, index = -1;
        for (int i = 0; i < n; i++) {
            if (!done[i]) {
                int dist = abs(req[i] - head);
                if (dist < min) {
                    min = dist;
                    index = i;
                }
            }
        }
        total += abs(req[index] - head);
        head = req[index];
        done[index] = 1;
        count++;
        printf(" -> %d", head);
    }
    printf("\nTotal Head Movement = %d\n", total);
}

// ============ SCAN (Elevator Algorithm) ============
void SCAN(int req[], int n, int head, int disk_size, int direction) {
    int total = 0, pos, i;
    int temp[100];

    for (i = 0; i < n; i++)
        temp[i] = req[i];
    temp[n++] = 0;
    temp[n++] = disk_size - 1;

    sort(temp, n);

    for (i = 0; i < n; i++)
        if (head < temp[i]) break;
    pos = i;

    printf("\nSCAN Disk Scheduling Order: %d", head);

    if (direction == 1) { // Moving right
        for (i = pos; i < n; i++) {
            total += abs(temp[i] - head);
            head = temp[i];
            printf(" -> %d", head);
        }
        for (i = pos - 1; i >= 0; i--) {
            total += abs(temp[i] - head);
            head = temp[i];
            printf(" -> %d", head);
        }
    } else { // Moving left
        for (i = pos - 1; i >= 0; i--) {
            total += abs(temp[i] - head);
            head = temp[i];
            printf(" -> %d", head);
        }
        for (i = pos; i < n; i++) {
            total += abs(temp[i] - head);
            head = temp[i];
            printf(" -> %d", head);
        }
    }
    printf("\nTotal Head Movement = %d\n", total);
}

// ============ C-SCAN (Circular SCAN) ============
void CSCAN(int req[], int n, int head, int disk_size) {
    int total = 0, pos, i;
    int temp[100];

    for (i = 0; i < n; i++)
        temp[i] = req[i];
    temp[n++] = 0;
    temp[n++] = disk_size - 1;

    sort(temp, n);

    for (i = 0; i < n; i++)
        if (head < temp[i]) break;
    pos = i;

    printf("\nC-SCAN Disk Scheduling Order: %d", head);

    for (i = pos; i < n; i++) {
        total += abs(temp[i] - head);
        head = temp[i];
        printf(" -> %d", head);
    }

    // Jump to beginning
    total += (disk_size - 1 - 0);
    head = 0;

    for (i = 0; i < pos; i++) {
        total += abs(temp[i] - head);
        head = temp[i];
        printf(" -> %d", head);
    }

    printf("\nTotal Head Movement = %d\n", total);
}

// ============ C-LOOK ============
void CLOOK(int req[], int n, int head) {
    int total = 0, pos, i;
    int temp[100];

    for (i = 0; i < n; i++)
        temp[i] = req[i];

    sort(temp, n);

    for (i = 0; i < n; i++)
        if (head < temp[i]) break;
    pos = i;

    printf("\nC-LOOK Disk Scheduling Order: %d", head);

    for (i = pos; i < n; i++) {
        total += abs(temp[i] - head);
        head = temp[i];
        printf(" -> %d", head);
    }

    for (i = 0; i < pos; i++) {
        total += abs(temp[i] - head);
        head = temp[i];
        printf(" -> %d", head);
    }

    printf("\nTotal Head Movement = %d\n", total);
}

// ============ Main Menu ============
int main() {
    int n, req[100], head, ch, disk_size, direction;

    printf("Enter number of requests: ");
    scanf("%d", &n);
    printf("Enter request queue: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &req[i]);
    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter total disk size: ");
    scanf("%d", &disk_size);

    do {
        printf("\n\n===== DISK SCHEDULING MENU =====");
        printf("\n1. SSTF");
        printf("\n2. SCAN");
        printf("\n3. C-SCAN");
        printf("\n4. C-LOOK");
        printf("\n5. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                SSTF(req, n, head);
                break;
            case 2:
                printf("Enter direction (1 for right, 0 for left): ");
                scanf("%d", &direction);
                SCAN(req, n, head, disk_size, direction);
                break;
            case 3:
                CSCAN(req, n, head, disk_size);
                break;
            case 4:
                CLOOK(req, n, head);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (ch != 5);

    return 0;
}
