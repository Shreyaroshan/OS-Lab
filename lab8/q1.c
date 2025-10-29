#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

// Function to check if the system is in a safe state
bool is_safe_state(int processes, int resources, int available[], int max[][MAX_RESOURCES], int alloc[][MAX_RESOURCES]) {
    int need[processes][resources];

    // Step 1: Calculate the Need matrix
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Step 2: Create Work and Finish arrays
    int work[resources];
    bool finish[processes];
   
    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    for (int i = 0; i < processes; i++) {
        finish[i] = false;
    }

    // Step 3: Try to find a process that can be finished
    int count = 0;
    while (count < processes) {
        bool progress = false;
       
        for (int i = 0; i < processes; i++) {
            if (!finish[i]) {
                // Check if process i can be finished
                bool can_finish = true;
                for (int j = 0; j < resources; j++) {
                    if (need[i][j] > work[j]) {
                        can_finish = false;
                        break;
                    }
                }

                if (can_finish) {
                    // Allocate resources to process i
                    for (int j = 0; j < resources; j++) {
                        work[j] += alloc[i][j];
                    }
                    finish[i] = true;
                    count++;
                    progress = true;
                    break;
                }
            }
        }

        // If no progress is made, the system is in an unsafe state
        if (!progress) {
            return false;
        }
    }

    return true;
}

// Function to request resources for a process
bool request_resources(int process, int request[], int processes, int resources, int available[], int max[][MAX_RESOURCES], int alloc[][MAX_RESOURCES]) {
    // Step 1: Check if request is less than or equal to Need
    for (int i = 0; i < resources; i++) {
        if (request[i] > max[process][i] - alloc[process][i]) {
            printf("Error: Process has exceeded maximum claim\n");
            return false;
        }
    }

    // Step 2: Check if request is less than or equal to Available
    for (int i = 0; i < resources; i++) {
        if (request[i] > available[i]) {
            printf("Error: Not enough resources available\n");
            return false;
        }
    }

    // Step 3: Pretend to allocate resources to the process
    for (int i = 0; i < resources; i++) {
        available[i] -= request[i];
        alloc[process][i] += request[i];
    }

    // Step 4: Check if the system is in a safe state
    if (is_safe_state(processes, resources, available, max, alloc)) {
        printf("Resources allocated successfully!\n");
        return true;
    } else {
        // If the system is not in a safe state, roll back the allocation
        for (int i = 0; i < resources; i++) {
            available[i] += request[i];
            alloc[process][i] -= request[i];
        }
        printf("Error: Request cannot be granted due to unsafe state\n");
        return false;
    }
}

// Function to display the current system status
void display_status(int processes, int resources, int available[], int max[][MAX_RESOURCES], int alloc[][MAX_RESOURCES]) {
    printf("\nSystem Status:\n");
    printf("Available Resources: ");
    for (int i = 0; i < resources; i++) {
        printf("%d ", available[i]);
    }
    printf("\n");

    printf("Max Matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }

    printf("Alloc Matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            printf("%d ", alloc[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int processes, resources;

    // Input the number of processes and resources
    printf("Enter the number of processes: ");
    scanf("%d", &processes);
    printf("Enter the number of resources: ");
    scanf("%d", &resources);

    // Initialize matrices for Max, Alloc, Available
    int max[MAX_PROCESSES][MAX_RESOURCES], alloc[MAX_PROCESSES][MAX_RESOURCES], available[MAX_RESOURCES];

    // Input the Maximum Resources required by each process
    printf("Enter the maximum resource matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            printf("Max[%d][%d]: ", i, j);
            scanf("%d", &max[i][j]);
        }
    }

    // Input the Allocated resources matrix
    printf("Enter the allocated resource matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            printf("Alloc[%d][%d]: ", i, j);
            scanf("%d", &alloc[i][j]);
        }
    }

    // Input the Available resources
    printf("Enter the available resources vector: ");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &available[i]);
    }

    // Display the initial status
    display_status(processes, resources, available, max, alloc);

    // Simulate resource request
    int process, request[MAX_RESOURCES];
    printf("Enter the process number (0 to %d) requesting resources: ", processes - 1);
    scanf("%d", &process);
    printf("Enter the resource request for Process %d:\n", process);
    for (int i = 0; i < resources; i++) {
        printf("Request for Resource %d: ", i);
        scanf("%d", &request[i]);
    }

    // Process the request
    request_resources(process, request, processes, resources, available, max, alloc);

    // Display the system status after request processing
    display_status(processes, resources, available, max, alloc);

    return 0;
}
