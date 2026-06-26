#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5
#define INCREMENTS 100000

int counter = 0;
pthread_mutex_t mutex;

// Function WITH mutex
void *increment_with_mutex(void *arg) {
    for (int i = 0; i < INCREMENTS; i++) {
        pthread_mutex_lock(&mutex);
        counter++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

// Function WITHOUT mutex
void *increment_without_mutex(void *arg) {
    for (int i = 0; i < INCREMENTS; i++) {
        counter++;
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // WITHOUT MUTEX
    counter = 0;
    printf("===== WITHOUT MUTEX =====\n");

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment_without_mutex, NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Expected Counter: %d\n", NUM_THREADS * INCREMENTS);
    printf("Actual Counter: %d\n\n", counter);

    // WITH MUTEX
    counter = 0;
    pthread_mutex_init(&mutex, NULL);

    printf("===== WITH MUTEX =====\n");

    for (int i = 0; i <
