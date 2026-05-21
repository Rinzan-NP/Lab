#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define SIZE 5

// Shared buffer

int buffer[SIZE];

// Circular queue pointers

int in = 0;
int out = 0;

// Semaphores

sem_t empty;
sem_t full;
sem_t mutex;

// =====================================
// CONSUMER
// =====================================

void* consumer(void* args){

    while(1){

        // Wait if buffer empty

        sem_wait(&full);

        // Lock buffer

        sem_wait(&mutex);

        // Consume item

        int item = buffer[out];

        out = (out + 1) % SIZE;

        printf("Consumed %d\n", item);

        // Unlock buffer

        sem_post(&mutex);

        // One more empty slot

        sem_post(&empty);

        sleep(2);
    }
}

// =====================================
// PRODUCER
// =====================================

void* producer(void* args){

    int item = 1;

    while(1){

        // Wait if buffer full

        sem_wait(&empty);

        // Lock buffer

        sem_wait(&mutex);

        // Produce item

        buffer[in] = item;

        in = (in + 1) % SIZE;

        printf("Produced %d\n", item);

        item++;

        // Unlock buffer

        sem_post(&mutex);

        // One more filled slot

        sem_post(&full);

        sleep(1);
    }
}

// =====================================
// MAIN
// =====================================

int main(){

    pthread_t p;
    pthread_t c;

    // mutex = 1
    // empty = SIZE
    // full = 0

    sem_init(&mutex, 0, 1);

    sem_init(&empty, 0, SIZE);

    sem_init(&full, 0, 0);

    // Create threads

    pthread_create(&p,
                   NULL,
                   producer,
                   NULL);

    pthread_create(&c,
                   NULL,
                   consumer,
                   NULL);

    // Keep program running

    pthread_join(p, NULL);

    pthread_join(c, NULL);

    return 0;
}