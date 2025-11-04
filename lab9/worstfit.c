#include <stdio.h>
#include <stdlib.h>

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int *allocation = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    printf("\nFirst Fit Allocation:\n");
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i+1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i]+1);
        else
            printf("Not Allocated\n");
    }
    free(allocation);
}

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int *allocation = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    printf("\nBest Fit Allocation:\n");
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i+1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i]+1);
        else
            printf("Not Allocated\n");
    }
    free(allocation);
}

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int *allocation = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }

    printf("\nWorst Fit Allocation:\n");
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i+1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i]+1);
        else
            printf("Not Allocated\n");
    }
    free(allocation);
}

int main() {
    int m, n;

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);
    int *blockSize = (int *)malloc(m * sizeof(int));
    printf("Enter size of each block:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &blockSize[i]);

    printf("Enter number of processes: ");
    scanf("%d", &n);
    int *processSize = (int *)malloc(n * sizeof(int));
    printf("Enter size of each process:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &processSize[i]);

    // Copy original block sizes for each strategy
    int *blockSizeFF = (int *)malloc(m * sizeof(int));
    int *blockSizeBF = (int *)malloc(m * sizeof(int));
    int *blockSizeWF = (int *)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        blockSizeFF[i] = blockSize[i];
        blockSizeBF[i] = blockSize[i];
        blockSizeWF[i] = blockSize[i];
    }

    firstFit(blockSizeFF, m, processSize, n);
    bestFit(blockSizeBF, m, processSize, n);
    worstFit(blockSizeWF, m, processSize, n);

    free(blockSize);
    free(processSize);
    free(blockSizeFF);
    free(blockSizeBF);
    free(blockSizeWF);

    return 0;
}
