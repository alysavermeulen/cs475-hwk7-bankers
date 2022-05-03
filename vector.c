#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

// TODO - Define vector and matrix operations

/**
 * Clones (deep copy) a vector
 * @param vector The vector being cloned
 * @return a clone (deep copy) of the vector
 */
int* clone_vector(int *vector, int length){
    int *clone = (int *)malloc(length * sizeof(int));
    int i;
    for (i = 0; i < length; i++){ // clone vector
        clone[i] = vector[i];
    }
    return clone;
}

/**
 * Clones (deep copy) a matrix
 * @param matrix The matrix being cloned
 * @return a clone (deep copy) of the matrix
 */
int** clone_matrix(int **matrix, int numRows, int numCols){
    int i, j;
    int **clone = (int **)malloc(numRows * sizeof(int *));
    for (i = 0; i < numRows; i++){ // dynamically allocate memory for each row in matrix
        clone[i] = (int *)malloc(numCols * sizeof(int));
    }
    for (i = 0; i < numRows; i++){ // clone matrix
        for (j = 0; j < numCols; j++){
            clone[i][j] = matrix[i][j];
        }
    }
    return clone;
}

/**
 * Compares two vectors and checks for equality
 * @param v1 The first vector
 * @param v2 The second vector
 * @return 1 if vectors are equal; 0 if not
 */
int compare(int *v1, int *v2, int length){
    int i;
    for (i = 0; i < length; i++){
        if (v1[i] != v2[i]){ // if vectors are not equal at this index
            return 0;
        }
    }
    return 1;
}

/**
 * Adds two vectors
 * @param v1 The first vector
 * @param v2 The second vector
 * @return a vector containing the result of v1 + v2
 */
int* add_vectors(int *v1, int *v2, int length){
    int *result = (int *)malloc(length * sizeof(int));
    int i;
    for (i = 0; i < length; i++){
        result[i] = v1[i] + v2[i];
    }
    return result;
}

/**
 * Subtracts two vectors
 * @param v1 The first vector
 * @param v2 The second vector
 * @return a vector containing the result of v1 - v2
 */
int* subtract_vectors(int *v1, int *v2, int length){
    int *result = (int *)malloc(length * sizeof(int));
    int i;
    for (i = 0; i < length; i++){
        result[i] = v1[i] - v2[i];
    }
    return result;
}

/**
 * Adds two matrices
 * @param m1 The first matrix
 * @param m2 The second matrix
 * @return a matrix containing the result of m1 + m2
 */
int** add_matrices(int **m1, int **m2, int numRows, int numCols){
    int i, j;
    int **result = (int **)malloc(numRows * sizeof(int *));
    for (i = 0; i < numRows; i++){ // dynamically allocate memory for each row in matrix
        result[i] = (int *)malloc(numCols * sizeof(int));
    }
    for (i = 0; i < numRows; i++){ // clone matrix
        for (j = 0; j < numCols; j++){
            result[i][j] = m1[i][j] + m2[i][j];
        }
    }
    return result;
}

/**
 * Subtracts two matrices
 * @param m1 The first matrix
 * @param m2 The second matrix
 * @return a matrix containing the result of m1 - m2
 */
int** subtract_matrices(int **m1, int **m2, int numRows, int numCols){
    int i, j;
    int **result = (int **)malloc(numRows * sizeof(int *));
    for (i = 0; i < numRows; i++){ // dynamically allocate memory for each row in matrix
        result[i] = (int *)malloc(numCols * sizeof(int));
    }
    for (i = 0; i < numRows; i++){ // clone matrix
        for (j = 0; j < numCols; j++){
            result[i][j] = m1[i][j] - m2[i][j];
        }
    }
    return result;
}

/**
 * Prints the contents of a vector
 * @param vector The vector being printed
 */
void print_vector(int *vector, int length){
    int i;
    for (i = 0; i < length; i++){
        printf("%d ", vector[i]);
    }
}

/**
 * Prints the contents of a matrix
 * @param matrix The matrix being printed
 */
void print_matrix(int **matrix, int numRows, int numCols){
    int i, j;
    for (i = 0; i < numRows; i++){
        for (j = 0; j < numCols; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

/**
 * Frees up memory allocated to a matrix
 * @param matrix The matrix being freed
 */
void free_matrix(int **matrix, int numRows){
    int i;
    for (i = 0; i < numRows; i++){ // free each row in matrix
	    free(matrix[i]);
	}
    free(matrix);
}