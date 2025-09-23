#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Process {
    int pid;
    int bt;     // burst time
    int at;     // arrival time
    int pr;     // priority
    int ct;     // completion time
    int tat;    // turnaround time
    int wt;     // waiting time
    int rt;     // remaining time
};

void calculate_and_display(struct Process p[], int n) {
    float avg_tat = 0, avg_wt = 0;
    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt  = p[i].tat - p[i].bt;
        avg_tat += p[i].tat;
        avg_wt  += p[i].wt;
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].pr,
               p[i].ct, p[i].tat, p[i].wt);
    }
    printf("\nAverage TAT = %.2f", avg_tat / n);
    printf("\nAverage WT  = %.2f\n", avg_wt / n);
}

// ---------------- Preemptive SJF ----------------
void preemptive_sjf(struct Process p[], int n) {
    int complete = 0, t = 0, min_index;
    for (int i = 0; i < n; i++)
        p[i].rt = p[i].bt;

    while (complete != n) {
        min_index = -1;
        int min_rt = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= t && p[i].rt > 0 && p[i].rt < min_rt) {
                min_rt = p[i].rt;
                min_index = i;
            }
        }

        if (min_index == -1) {
            t++;
            continue;
        }

        p[min_index].rt--;
        t++;

        if (p[min_index].rt == 0) {
            complete++;
            p[min_index].ct = t;
        }
    }
    printf("\n--- Preemptive SJF Scheduling ---\n");
    calculate_and_display(p, n);
}

// ---------------- Round Robin ----------------
void round_robin(struct Process p[], int n, int quantum) {
    int t = 0, done;
    for (int i = 0; i < n; i++)
        p[i].rt = p[i].bt;

    do {
        done = 1;
        for (int i = 0; i < n; i++) {
            if (p[i].rt > 0) {
                done = 0;
                if (p[i].rt > quantum) {
                    t += quantum;
                    p[i].rt -= quantum;
                } else {
                    t += p[i].rt;
                    p[i].ct = t;
                    p[i].rt = 0;
                }
            }
        }
    } while (!done);

    printf("\n--- Round Robin Scheduling (Quantum=%d) ---\n", quantum);
    calculate_and_display(p, n);
}

// ---------------- Non-preemptive Priority ----------------
void non_preemptive_priority(struct Process p[], int n) {
    int completed = 0, t = 0;
    int done[50] = {0};

    while (completed != n) {
        int max_pr = INT_MIN, idx = -1;
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= t) {
                if (p[i].pr > max_pr) {
                    max_pr = p[i].pr;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            t++;
            continue;
        }

        t += p[idx].bt;
        p[idx].ct = t;
        done[idx] = 1;
        completed++;
    }

    printf("\n--- Non-preemptive Priority Scheduling ---\n");
    calculate_and_display(p, n);
}

// ---------------- Main Menu ----------------
int main() {
    int n, choice, quantum;
    struct Process p[50];

    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nProcess %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        printf("Priority (higher = better): ");
        scanf("%d", &p[i].pr);
    }

    do {
        printf("\n\n--- CPU Scheduling Menu ---\n");
        printf("1. Preemptive SJF\n");
        printf("2. Round Robin\n");
        printf("3. Non-preemptive Priority\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                preemptive_sjf(p, n);
                break;
            case 2:
                printf("Enter time quantum: ");
                scanf("%d", &quantum);
                round_robin(p, n, quantum);
                break;
            case 3:
                non_preemptive_priority(p, n);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}
