#ifndef VECTOR_H_
#define VECTOR_H_

// function prototypes of vector and matrix operations
int* clone_vector(int *vector, int length);
int** clone_matrix(int **matrix, int numRows, int numCols);
int compare(int *v1, int *v2, int length);
int* add_vectors(int *v1, int *v2, int length);
int* subtract_vectors(int *v1, int *v2, int length);
int** add_matrices(int **m1, int **m2, int numRows, int numCols);
int** subtract_matrices(int **m1, int **m2, int numRows, int numCols);
void print_vector(int *vector, int length);
void print_matrix(int **matrix, int numRows, int numCols);
void free_matrix(int **matrix, int numRows);


#endif /* VECTOR_H_ */