#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vector.h"
#include "banker.h"

int **a; // allocation matrix
int **n; // need matrix
int numT; // number of threads
int numR; // number of resources

/**
 * Beginning of Banker's Safety algorithm; mainly constructs necessary arrays and then
 * calls the recursive function to find all safe schedules (or deem the state unsafe)
 * @param available An array holding the counts of available resources
 * @param alloc The allocation matrix, showing which resources are allocated to each thread
 * @param need The need matrix, showing which resources each thread still needs
 * @param numThreads The number of threads
 * @param numResources The number of resources
 */
void isSafe(int *available, int **alloc, int **need, int numThreads, int numResources){
    a = alloc;
    n = need;
    numT = numThreads;
    numR = numResources;
    // array holding counts of still available resources (clone of available array)
    int *work = clone_vector(available, numResources);
    // array holding safe schedule being constructed
    int *safe = (int *)malloc(numThreads * sizeof(int));
    // array tracking which threads have finished
    int *finish = (int *)malloc(numThreads * sizeof(int));
    int i;
    for (i = 0; i < numT; i++){
        finish[i] = 0; // initialize with zeroes since no threads have finished
    }
    findAllSafe(work, safe, finish, 0);
    free(work);
    free(safe);
    free(finish);
}

/**
 * Recursively determines whether the state is safe or unsafe, and if it is safe,
 * recursively finds and lists all safe schedules
 * @param work An array holding the counts of available resources
 * @param safe An array holding the safe schedule being constructed
 * @param finish An array tracking which threads have finished
 * @param numFinished // Tracks how many threads have finished in a given schedule
 */
void findAllSafe(int *work, int *safe, int *finish, int numFinished){
    int i, j;
    bool canComplete; // tracks which threads can finish
    bool s = false; // tracks whether at least one thread can finish
    int *canFinish = (int *)malloc(numT * sizeof(int)); // array showing which threads can finish
    for (i = 0; i < numT; i++){
        canFinish[i] = 0;
    }
    if (numFinished == numT){ // if all threads have finished, schedule is safe
        printf("SAFE: ");
        for (j = 0; j < numT; j++){
            printf("T%d ", safe[j]);
        }
        printf("\n");
        return;
    }
    for (i = 0; i < numT; i++){
        if (finish[i] == 0){ // if thread i has not finished yet
            canComplete = true;
            for (j = 0; j < numR; j++){
                if (n[i][j] > work[j]){ // thread's needs exceed the available resources
                    canComplete = false;
                }
            }
            if (canComplete == true){ // thread's needs do not exceed the available resources
                canFinish[i] = 1;
                s = true; // at least one thread can run
            }
        }
    }
    if (s == false){ // if no threads can run (and not all threads have finished)
        printf("UNSAFE: ");
        for (j = 0; j < numT; j++){
            if (finish[j] == 0){
                printf("T%d ", j);
            }
        }
        printf("can't finish\n");
        return;
    }
    for (j = 0; j < numT; j++){
        if (canFinish[j] == 1){ // if thread j can finish
            // simulate running the thread
            safe[numFinished] = j; // add thread to safe schedule
            numFinished++;
            work = add_vectors(work, a[j], numR);
            finish[j] = 1;
            findAllSafe(work, safe, finish, numFinished); // recursively find safe schedules
            // undo changes made to simulate thread running
            finish[j] = 0;
            work = subtract_vectors(work, a[j], numR);
            numFinished--;
        }
    }
    free(canFinish);
}