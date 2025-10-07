#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 1000  // Size of the matrix
#define NUM_THREADS 1  // Number of threads

int **A, **B, **C;  // Global matrices

// Structure to hold information for each thread
typedef struct 
{
    int thread_id;
    int num_rows;  // Number of rows each thread will handle
} thread_data_t;

// Function for each thread to perform matrix multiplication
void* matrixMultiplyThread(void* arg) 
{
    long id = (long)arg;
    // Divide the task (rows) of each thread based on thread id
    // compute a portion of the matrix multiplication
    int divide = (N + NUM_THREADS - 1) / NUM_THREADS;
    int start = id * divide;
    int end = (start + divide > N) ? N : start + divide;
    
    for (long i = start; i < end; i++) {
        for (long j = 0; j < N; j++) {
            for (long m = 0; m < N; m++) {
                C[i][j] += A[i][m] * B[m][j];
            }
        }
    }

    pthread_exit(NULL);
}

void displayMatrix(int** matrix, int n) 
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}