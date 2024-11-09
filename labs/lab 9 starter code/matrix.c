#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include "matrix.h"

/* Creates and returns a matrix of size nrows x ncols
 * If the allocation is not successful, the function should return NULL.
 * If the allocation is successful, the data field of the matrix points to an array of pointers (representing the rows).
 * Each pointer in that array points to an array of int representing the values in that row.
 */
TMatrix * newMatrix(unsigned int nrows, unsigned int ncols) {
    if (! nrows || ! ncols)                                         /* Checks that nrows and ncols are non-zero values */
        return NULL;

    TMatrix* newM = malloc(sizeof(TMatrix));                        /* Allocate space for TMatrix */
    int** data = malloc(nrows * sizeof(int*));                      /* Allocate space for a nrows x ncols matrix */
    int* storage = malloc(nrows * ncols * sizeof(int));             /* Allocate space for all elements in one call */

    if (newM == NULL || data == NULL || storage == NULL) {          /* Error checking */
        free(newM);
        free(data);
        free(storage);
        return NULL;
    }

    /* set row array pointers */
    for (size_t i = 0; i < nrows; i++)
            data[i] = storage + i * ncols;
    newM->nrows = nrows;
    newM->ncols = ncols;
    newM->data = data;
    
    return newM;
}

/* Deallocates the dynamic memory used by a matrix. */
void freeMatrix(TMatrix * m) {
    if (m == NULL)          
        return;
    if (m->data)  {
        free(m->data[0]);   /* free the storage allocated for data */
        free(m->data);      /* free the array of pointers to row pointers */
    }
    free(m);                /* free the matrix itself */
}

/* Fill the matrix with random int values. */
TMatrix * fillMatrix(TMatrix * m) {
    if (m == NULL || m->data == NULL)
        return m;

    srand(3100);
    unsigned int i, j;
    for (i = 0; i < m->nrows; i ++)
        for (j = 0; j < m->ncols; j ++)
            m->data[i][j] = (int)rand() % 100;
    return m;
}

/* Prints the elements in a matrix m. */
void printMatrix(TMatrix * m) {
    if (m == NULL)
        return;
    for (unsigned int i = 0; i < m->nrows; i++) {
        for (unsigned int j = 0; j < m->ncols; j++)
            printf("%5d", m->data[i][j]);
        printf("\n");
    }
    printf("\n");
}

/* This function compares two matrices m and n. */
int compareMatrix(TMatrix * m, TMatrix *n) {
    if (m == NULL || n == NULL)     /* Return -1 if either matrices are NULL */
        return -1;                      

    unsigned i, j;
    for (i = 0; i < m->nrows; i ++)
        for (j = 0; j < m->ncols; j ++)
            if (m->data[i][j] != n->data[i][j]) {
                fprintf(stderr, "element[%u][%u]  %d  %d.\n", i, j, m->data[i][j], n->data[i][j]);
                return 1;           /* Return 1 if the 2 matrices are different. print the first different element on stdout. */
            }
    
    return 0;                       /* Return 0 if m and n are the same */
}

/* Add two matrices m and n and return their sum. This function is implemented using a single thread */
TMatrix * addMatrix(TMatrix *m, TMatrix *n) {
    if (m == NULL || n == NULL || m->nrows != n->nrows || m->ncols != n->ncols )
        return NULL;

    TMatrix * t = newMatrix(m->nrows, m->ncols);
    if (t == NULL)
        return t;
    for (unsigned int i = 0; i < m->nrows; i++)
        for (unsigned int j = 0; j < m->ncols; j++)
            t->data[i][j] = m->data[i][j] + n->data[i][j];

    return t;
}

/* The function executed by the threads */
static void * thread_main(void * p_arg) {
    thread_arg_t *arg = (thread_arg_t *)p_arg;
    int rows_per_thread = arg->m->nrows / arg->num_threads;
    int start_row = arg->id * rows_per_thread;
    int end_row = (arg->id == arg->num_threads - 1) ? arg->m->nrows : start_row + rows_per_thread;

    // Add the respective rows from matrices m and n, store in t
    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < arg->m->ncols; j++) {
            arg->t->data[i][j] = arg->m->data[i][j] + arg->n->data[i][j];
        }
    }
    /* TODO 
        * This is the function executed by each thread.
        * Each thread must add a subset of the total number of rows.
        * The work must be divided among the threads as evenly as possible. 
        * The partial results must be stored.
    */
   
    return NULL;
}

/* Add two matrices m and n and return their sum. This function is implemented using nbT threads */
TMatrix * addMatrix_thread(int nbT, TMatrix *m, TMatrix *n) {
    if (m == NULL || n == NULL || m->nrows != n->nrows || m->ncols != n->ncols )
        return NULL;

    TMatrix * t = newMatrix(m->nrows, m->ncols);
    if (t == NULL)
        return t;

    pthread_t threads[nbT];
    thread_arg_t thread_args[nbT];
    // Create and initialize threads
    for (int i = 0; i < nbT; i++) {
        thread_args[i].num_threads = nbT;
        thread_args[i].id = i;
        thread_args[i].m = m;
        thread_args[i].n = n;
        thread_args[i].t = t;
        pthread_create(&threads[i], NULL, thread_main, &thread_args[i]);
    }

    // Wait for all threads to complete
    for (int i = 0; i < nbT; i++) {
        pthread_join(threads[i], NULL);
    }


    /* TODO: 
        * Create nbT number of threads. 
        * Each thread calls the thread_main function and takes its own argument. 
        * The argument contains a pointer to the matrices m, n and t, total number of threads nbT and the thread id which is an int and ranges from 0 to nbT-1.
        *
        * Wait for the threads to complete their computation. 
        * Return t. 
        
    */
   
    return t;
}



