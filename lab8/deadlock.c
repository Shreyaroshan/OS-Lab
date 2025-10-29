#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

// Function to perform depth-first search (DFS) to check for cycles
bool dfs(int process, bool visited[], bool recursion_stack[], int adj_matrix[MAX_PROCESSES][MAX_PROCESSES]) {
    if (recursion_stack[process]) {
        return true; // Cycle detected
    }

    if (visited[process]) {
        return false; // Already visited and no cycle found
    }

    visited[process] = true;
    recursion_stack[process] = true;

    // Recur for all processes that this process is waiting for
    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (adj_matrix[process][i] == 1 && dfs(i, visited, recursion_stack, adj_matrix)) {
            return true; // Cycle found
        }
    }

    recursion_stack[process] = false;
    return false;
}

// Function to check if there is a deadlock by detecting a cycle in the graph
bool detect_deadlock(int adj_matrix[MAX_PROCESSES][MAX_PROCESSES], int num_processes) {
    bool visited[MAX_PROCESSES] = {0};
    bool recursion_stack[MAX_PROCESSES] = {0};

    for (int i = 0; i < num_processes; i++) {
        if (!visited[i] && dfs(i, visited, recursion_stack, adj_matrix)) {
            return true; // Cycle detected, so deadlock exists
        }
    }

    return false; // No cycle detected, no deadlock
}

void print_graph(int adj_matrix[MAX_PROCESSES][MAX_PROCESSES], int num_processes) {
    printf("\nWait-for Graph (Adjacency Matrix):\n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_processes; j++) {
            printf("%d ", adj_matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int num_processes, num_resources;

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    // Input number of resources
    printf("Enter the number of resources: ");
    scanf("%d", &num_resources);

    // Initialize the adjacency matrix (Wait-for graph)
    int adj_matrix[MAX_PROCESSES][MAX_PROCESSES] = {0};

    // Input the allocation information
    for (int i = 0; i < num_processes; i++) {
        printf("For Process %d:\n", i + 1);
        printf("Enter the processes that Process %d is waiting for (enter 1 if waiting, 0 otherwise):\n", i + 1);
       
        for (int j = 0; j < num_processes; j++) {
            printf("Is Process %d waiting for Process %d? (1/0): ", i + 1, j + 1);
            scanf("%d", &adj_matrix[i][j]);
        }
    }

    // Print the wait-for graph
    print_graph(adj_matrix, num_processes);

    // Check for deadlock
    if (detect_deadlock(adj_matrix, num_processes)) {
        printf("\nDeadlock detected!\n");
    } else {
        printf("\nNo deadlock detected.\n");
    }

    return 0;
}
