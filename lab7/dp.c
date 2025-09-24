#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t chopstick[N];

void *philosopher(void *num) {
    int id = *(int *)num;
    while (1) {
        printf("Philosopher %d is thinking\n", id);
        sleep(1);

        sem_wait(&chopstick[id]);
        sem_wait(&chopstick[(id + 1) % N]);

        printf("Philosopher %d is eating\n", id);
        sleep(2);

        sem_post(&chopstick[id]);
        sem_post(&chopstick[(id + 1) % N]);

        printf("Philosopher %d finished eating\n", id);
    }
}

int main() {
    pthread_t phil[N];
    int id[N];

    for (int i = 0; i < N; i++) {
        sem_init(&chopstick[i], 0, 1);
        id[i] = i;
    }

    for (int i = 0; i < N; i++)
        pthread_create(&phil[i], NULL, philosopher, &id[i]);

    for (int i = 0; i < N; i++)
        pthread_join(phil[i], NULL);

    for (int i = 0; i < N; i++)
        sem_destroy(&chopstick[i]);

    return 0;
}
