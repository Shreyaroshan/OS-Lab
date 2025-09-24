
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t rw_mutex, mutex;
int read_count = 0, data = 0;

void *reader(void *arg) {
    int f = ((int)arg);
    sem_wait(&mutex);
    read_count++;
    if (read_count == 1)
        sem_wait(&rw_mutex);
    sem_post(&mutex);

    printf("Reader %d reads data = %d\n", f, data);
    sleep(1);

    sem_wait(&mutex);
    read_count--;
    if (read_count == 0)
        sem_post(&rw_mutex);
    sem_post(&mutex);
    return NULL;
}

void *writer(void *arg) {
    int f = ((int)arg);
    sem_wait(&rw_mutex);
    data++;
    printf("Writer %d writes data = %d\n", f, data);
    sleep(1);
    sem_post(&rw_mutex);
    return NULL;
}
int main() {
    pthread_t r[5], w[5];
    sem_init(&rw_mutex, 0, 1);
    sem_init(&mutex, 0, 1);

    for (int i = 0; i < 5; i++) {
        pthread_create(&w[i], NULL, writer, (void *)i);
        pthread_create(&r[i], NULL, reader, (void *)i);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(w[i], NULL);
        pthread_join(r[i], NULL);
    }

    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);
    return 0;
}
