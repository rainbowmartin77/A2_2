#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 100000000
#define NUM_THREADS 4

long long arr[SIZE];
long long partialSums[NUM_THREADS] = {0}; // Array to store partial sums for each thread
long long divide = SIZE/NUM_THREADS;

// Entry function for each thread
void* sumPart(void* arg) 
{
    int id = *(int*)arg;

    // Divide the work for each thread based on their id and let them compute partial sums
    if (id == 0) {
        printf("Thread 0 started");
        for (int x = 0; x < divide; x++){
            partialSums[id] += arr[x];
        }
        prinf("Thread 0 completed, total is %lld.", partialSums[0]);
    }
    else if (id == 1) {
        printf("Thread 1 started");
        for (int x = divide; x < (divide * 2); x++){
            partialSums[id] += arr[x];
        }
        printf("Thread 1 completed, total is %lld.", partialSums[1]);
    }
    else if (id == 2) {
        printf("Thread 2 started");
        for (int x = (divide * 2); x < (divide * 3); x++){
            partialSums[id] += arr[x];
        }
        printf("Thread 2 completed, total is %lld.", partialSums[2]);
    }
    else {
        printf("Thread 3 started.");
        for (int x = (divide * 3); x < SIZE; x++){
            partialSums[id] += arr[x];
        }
        printf("Thread 3 completed, total is %lld.", partialSums[3]);
    }

    pthread_exit(NULL);
}

int main() 
{
    // Initialize the array
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i + 1; 
    }

    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Create threads to compute partial sums
    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, sumPart, &thread_ids[i]);
    }

    // Wait for all threads to finish
    for (long i = NUM_THREADS - 1; i >= 0; i--) {
        pthread_join(threads[i], NULL);
    }

    // Combine the partial sums from all threads
    long long totalSum = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        totalSum += partialSums[i];
    }

    // Print the total sum;
    printf("Total Sum: %lld\n", totalSum);

    return 0;
}
