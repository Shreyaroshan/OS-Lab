#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;            // Task ID
    int executionTime; // Execution time (C)
    int period;        // Period or deadline (T)
    int remainingTime; // Remaining execution time
    int nextDeadline;  // Next deadline time
} Task;

void rateMonotonic(Task tasks[], int n, int simulationTime) {
    printf("\n--- Rate Monotonic Scheduling (RMS) ---\n");

    // Initialize remaining times and next deadlines
    for (int i = 0; i < n; i++) {
        tasks[i].remainingTime = tasks[i].executionTime;
        tasks[i].nextDeadline = tasks[i].period;
    }

    for (int time = 0; time < simulationTime; time++) {
        int current = -1;
        int minPeriod = 9999;

        // Select task with smallest period (highest priority)
        for (int i = 0; i < n; i++) {
            if (tasks[i].remainingTime > 0 && tasks[i].period < minPeriod) {
                current = i;
                minPeriod = tasks[i].period;
            }
        }

        // Execute selected task
        if (current != -1) {
            printf("Time %2d - %2d : Task %d executing\n", time, time + 1, tasks[current].id);
            tasks[current].remainingTime--;
        } else {
            printf("Time %2d - %2d : Idle\n", time, time + 1);
        }

        // Check for period reset
        for (int i = 0; i < n; i++) {
            if ((time + 1) % tasks[i].period == 0) {
                if (tasks[i].remainingTime > 0)
                    printf("  >> Task %d MISSED DEADLINE!\n", tasks[i].id);
                tasks[i].remainingTime = tasks[i].executionTime;
            }
        }
    }
}

void earliestDeadlineFirst(Task tasks[], int n, int simulationTime) {
    printf("\n--- Earliest Deadline First Scheduling (EDF) ---\n");

    // Initialize remaining times and next deadlines
    for (int i = 0; i < n; i++) {
        tasks[i].remainingTime = tasks[i].executionTime;
        tasks[i].nextDeadline = tasks[i].period;
    }

    for (int time = 0; time < simulationTime; time++) {
        int current = -1;
        int earliestDeadline = 9999;

        // Select task with earliest upcoming deadline
        for (int i = 0; i < n; i++) {
            if (tasks[i].remainingTime > 0 && tasks[i].nextDeadline < earliestDeadline) {
                current = i;
                earliestDeadline = tasks[i].nextDeadline;
            }
        }

        // Execute selected task
        if (current != -1) {
            printf("Time %2d - %2d : Task %d executing\n", time, time + 1, tasks[current].id);
            tasks[current].remainingTime--;
        } else {
            printf("Time %2d - %2d : Idle\n", time, time + 1);
        }

        // Check for deadline reset
        for (int i = 0; i < n; i++) {
            if (time + 1 == tasks[i].nextDeadline) {
                if (tasks[i].remainingTime > 0)
                    printf("  >> Task %d MISSED DEADLINE!\n", tasks[i].id);
                tasks[i].remainingTime = tasks[i].executionTime;
                tasks[i].nextDeadline += tasks[i].period;
            }
        }
    }
}

int main() {
    int n, simulationTime;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    Task *tasks = (Task *)malloc(n * sizeof(Task));

    printf("Enter execution time and period (C T) for each task:\n");
    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        scanf("%d %d", &tasks[i].executionTime, &tasks[i].period);
    }

    printf("Enter total simulation time: ");
    scanf("%d", &simulationTime);

    rateMonotonic(tasks, n, simulationTime);
    earliestDeadlineFirst(tasks, n, simulationTime);

    free(tasks);
    return 0;
}
