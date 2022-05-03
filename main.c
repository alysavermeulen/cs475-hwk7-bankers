#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "banker.h"

int main(int argc, char *argv[])
{
  // attempt to open state file
  if (argc != 2){
		printf("Usage: ./bankers [name of state file]\n");
		exit(0);
	}
  FILE *fp;
  fp = fopen(argv[1], "r");
  if (fp == NULL){
    printf("File does not exist\n");
    exit(0);
  }

  // scan number of resource types and number of processes
  int NRES; 	// number of resource types (num columns)
  int NPROC;	// number of processes (num rows)
  fscanf(fp, "%d", &NRES);
  fscanf(fp, "%d", &NPROC);

  // allocate memory
  int *vector = (int *)malloc(NRES * sizeof(int)); // total resource vector
  int **maxMatrix = (int **)malloc(NPROC * sizeof(int *)); // max demand matrix
  int **allocMatrix = (int **)malloc(NPROC * sizeof(int *)); // allocation matrix
  int i;
  for (i = 0; i < NPROC; i++){ // dynamically allocate memory for each row in matrices
    maxMatrix[i] = (int *)malloc(NRES * sizeof(int));
		allocMatrix[i] = (int *)malloc(NRES * sizeof(int));
  }

  // scan memory into allocated structures
  int val;
  for (i = 0; i < NRES; i++){ // scan in total resource vector
    fscanf(fp, "%d", &val);
    vector[i] = val;
  }
  int j;
  for (i = 0; i < NPROC; i++){ // scan in max demand matrix
    for (j = 0; j < NRES; j++){
      fscanf(fp, "%d", &val);
      maxMatrix[i][j] = val;
    }
  }
  for (i = 0; i < NPROC; i++){ // scan in allocation matrix
    for (j = 0; j < NRES; j++){
      fscanf(fp, "%d", &val);
      allocMatrix[i][j] = val;
    }
  }

  // perform sanity check
  // ensure currently allocated resources do not exceed total number of resources
  int colSum; // holds sum of column in allocation matrix
  int num; // holds total number of resources associated with that column's resource type
  for (i = 0; i < NRES; i++){ // scan in max demand matrix
    colSum = 0;
    for (j = 0; j < NPROC; j++){
      colSum += allocMatrix[i][j];
    }
    num = vector[i];
    if (colSum > num){
      printf("Integrity test failed: allocated resources exceed total resources\n");
      free(vector);
      free_matrix(maxMatrix, NPROC);
      free_matrix(allocMatrix, NPROC);
      exit(0);
    }
  }
  // ensure each thread's needs do not exceed its max demands for each resource type
  for (i = 0; i < NPROC; i++){ // scan in allocation matrix
    for (j = 0; j < NRES; j++){
      if (allocMatrix[i][j] > maxMatrix[i][j]){
        printf("Integrity test failed: allocated resources exceed demand for Thread %d\n", i);
        printf("Need %d instances of resource %d\n", maxMatrix[i][j] - allocMatrix[i][j], j);
        free(vector);
        free_matrix(maxMatrix, NPROC);
        free_matrix(allocMatrix, NPROC);
        exit(0);
      }
    }
  }

  // run banker's safety algorithm
  int *available = (int *)malloc(NRES * sizeof(int));
  for (i = 0; i < NRES; i++){ // construct array holding counts of available resources
    colSum = 0;
    for (j = 0; j < NPROC; j++){
      colSum += allocMatrix[j][i];
    }
    available[i] = vector[i] - colSum;
  }
  // matrix showing which resources each thread still needs
  int **need = subtract_matrices(maxMatrix, allocMatrix, NPROC, NRES);

  isSafe(available, allocMatrix, need, NPROC, NRES);

  // free arrays and matrices
  free(vector);
  free(available);
  for (j = 0; j < NPROC; j++){ // free each row in matrices
			free(maxMatrix[j]);
      free(allocMatrix[j]);
      free(need[j]);
	}
	free(maxMatrix);
	free(allocMatrix);
	free(need);

  return 0;
}