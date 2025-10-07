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
    long id = (long)arg;

    long long divide = (SIZE + NUM_THREADS - 1) / NUM_THREADS;
    long long start = id * divide;
    long long end = (start + divide > SIZE) ? SIZE : start + divide;
    // Divide the work for each thread based on their id and let them compute partial sums

    for (long long i = start; i < end; i++) {
        partialSums[id] += arr[i];
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
        pthread_create(&threads[i], NULL, sumPart, (void *)i);
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
