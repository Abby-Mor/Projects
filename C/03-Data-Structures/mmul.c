#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "matrix.h"

// Search TODO to find the locations where code needs to be completed

#define     NUM_THREADS     2

typedef struct {
    unsigned int id;
    TMatrix *m, *n, *t;
} thread_arg_t;

static void * thread_main(void * p_arg)
{
    // TODO
    thread_arg_t *thread = (thread_arg_t*) p_arg; //fix the type of the structure thread
    //set all the variables to the structure ones
    int id = thread->id; 
    TMatrix *m = thread->m;
    TMatrix *n = thread->n;
    TMatrix *t = thread->t;

    int end;
    int rows_perthread = m-> nrows / NUM_THREADS;
    int start = id*rows_perthread;

    if (id == NUM_THREADS-1){
        end = m->nrows;
    }else
        end = (start + rows_perthread);

    for (unsigned int i = start; i < end; i++)  {
        for (unsigned int j = 0; j < n->ncols; j++) {
            double sum = 0.0;
            for (unsigned int k = 0; k < m->ncols; k++)
                sum += m->data[i][k] * n->data[k][j];
            t->data[i][j] = sum;
        }
    }
    return NULL;
}

/* Return the sum of two matrices.
 *
 * If any pthread function fails, report error and exit. 
 * Return NULL if anything else is wrong.
 *
 * Similar to mulMatrix, but with multi-threading.
 */
TMatrix * mulMatrix_thread(TMatrix *m, TMatrix *n)
{
    if (    m == NULL || n == NULL
         || m->ncols != n->nrows )
        return NULL;

    TMatrix * t = newMatrix(m->nrows, n->ncols);

    if (t == NULL)
        return t;

    thread_arg_t threads[NUM_THREADS]; //create the structures threads
    pthread_t ids[NUM_THREADS]; //create the actual threads

    //for each thread set the variables to the ones that were given in arguments
    for(int i = 0; i < NUM_THREADS; i++){
        threads[i].id = i;
        threads[i].m = m;
        threads[i].n = n;
        threads[i].t = t;
        pthread_create(&ids[i], NULL, thread_main, &threads[i]);
    }
    //wait for the previous threads before starting the next thread
    for(int i = 0; i<NUM_THREADS; i++){
        pthread_join(ids[i], NULL);
    }
    // TODO
    return t;
}
