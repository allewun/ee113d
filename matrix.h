//
// matrix.h
// Facial gender detection
//
//
// EE 113D - Fall 2013
//  * Allen Wu
//  * Bryant Khau
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

// Matrix data type
typedef struct {
    size_t width, height;
    double** data;
} Matrix;

// Helper functions
Matrix array2Matrix(double* array, size_t arrayLen, size_t height, size_t width);
void printMatrix(Matrix m, int decimals);
void freeMatrix(Matrix* m);

// Matrix/vector functions
double vectorNorm(Matrix a);
double max(Matrix a);
Matrix dotProduct(Matrix a, Matrix b);
Matrix transpose(Matrix input);
Matrix subtract(Matrix x, Matrix y);
Matrix column(Matrix m, int n);

Matrix arrayFun(double (*function)(double), Matrix m);