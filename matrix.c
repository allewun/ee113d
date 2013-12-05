//
// matrix.c
// Facial gender detection
//
//
// EE 113D - Fall 2013
//  * Allen Wu
//  * Bryant Khau
//

#include <stdio.h>
#include <math.h>
#include <float.h>
#include "matrix.h"

//=============================================================================
// Helper functions
//=============================================================================

// Convert a plain array to a Matrix struct
Matrix array2Matrix(double* array, size_t arrayLen, size_t rows, size_t cols) {
    Matrix result = {0};
    int i, h, w;

    // verify dimensions
    if (arrayLen != cols * rows) {
        return result;
    }

    // create matrix
    result = newMatrix(rows, cols, false);

    // populate data
    for (h = 0; h < rows; h++) {
        for (w = 0; w < cols; w++) {
            result.data[h][w] = array[h*cols + w];
        }
    }

    return result;
}

// Print matrix to console
void printMatrix(Matrix m) {
    int i, j;

    printf("\n");
    if (m.cols == 0 || m.rows == 0) {
        printf("[]\n");
        return;
    }
    for (i = 0; i < m.rows; i++) {
        for (j = 0; j < m.cols; j++) {
            if (i == 0 && j == 0) {
                printf("[ ");
            }
            else if (j == 0) {
                printf("  ");
            }
            printf("%.*f ", PRINT_MATRIX_DECIMALS, m.data[i][j]);
        }
        if (i == m.rows - 1) {
            printf("]");
        }
        printf("\n");
    }
}

// Free memory allocated for matrix data
void freeMatrix(Matrix* m) {
    int i;
    for (i = 0; i < m->rows; i++) {
        free(m->data[i]);
    }
    free(m->data);

    m->cols = 0;
    m->rows = 0;
    m->data = NULL;
}

// Allocate an rxc block of memory to be used for a matrix
Matrix newMatrix(size_t rows, size_t cols, bool clearMemory) {
    Matrix result = {0};
    double** data;
    int i;

    data = clearMemory ? calloc(rows, sizeof(double*)) : malloc(sizeof(double*) * rows);
    for (i = 0; i < rows; i++) {
        data[i] = clearMemory ? calloc(cols, sizeof(double)) : malloc(sizeof(double) * cols);
    }

    result.data = data;
    result.rows = rows;
    result.cols = cols;

    return result;
}


//=============================================================================
// Matrix/vector functions
//=============================================================================

// Calculate vector norm
double vectorNorm(Matrix a) {
    double sum = 0;
    int i, j;

    // calculate vector norm if matrix is a vector
    if (a.cols == 1) {
        for (i = 0; i < a.rows; i++) {
            sum += a.data[i][0] * a.data[i][0];
        }
    }
    else if (a.rows == 1) {
        for (i = 0; i < a.cols; i++) {
            sum += a.data[0][i] * a.data[0][i];
        }
    }
    // if matrix isn't a vector, don't compute norm
    // (matrix 2-norm is more complex and unneeded)
    else {
        return -1;
    }

    return sqrt(sum);
}

// Find max element of vector
Pair maxWithIndex(Matrix a) {
    double currentMax = -DBL_MAX;
    int currentIndex = -1;
    Pair result = {-1, -1};

    int r, c, rMax, cMax;

    if (a.rows == 1) {
        rMax = 1;
        cMax = a.cols;
    }
    else if (a.cols == 1) {
        rMax = a.rows;
        cMax = 1;
    }
    else {
        return result;
    }

    for (r = 0; r < rMax; r++) {
        for (c = 0; c < cMax; c++) {
            if (a.data[r][c] > currentMax) {
                currentMax = a.data[r][c];
                currentIndex = r+c;
            }
        }
    }

    result.value = currentMax;
    result.index = currentIndex;

    return result;
}

// Sum of all elements of matrix
double sum(Matrix a) {
    double result = 0;
    int r, c;

    for (r = 0; r < a.rows; r++) {
        for (c = 0; c < a.cols; c++) {
            result += a.data[r][c];
        }
    }
    return result;
}

// Perform matrix subtraction
Matrix subtract(Matrix a, Matrix b) {
    Matrix result = {0};
    int i, h, w;

    // verify dimensions
    if (a.cols != b.cols || a.rows != b.rows) {
        return result;
    }

    // create matrix
    result = newMatrix(a.rows, a.cols, false);

    // subtract
    for (h = 0; h < a.rows; h++) {
        for (w = 0; w < a.cols; w++) {
            result.data[h][w] = a.data[h][w] - b.data[h][w];
        }
    }

    return result;
}

// Perform matrix dot product
Matrix dotProduct(Matrix a, Matrix b) {
    Matrix result = {0};
    int i, h, w, yh;

    // verify dimensions
    if (a.cols != b.rows) {
        return result;
    }

    // create matrix
    result = newMatrix(a.rows, b.cols, true);

    // dot product
    for (h = 0; h < a.rows; h++) {
        for (w = 0; w < b.cols; w++) {
            for (yh = 0; yh < b.rows; yh++) {
                result.data[h][w] += a.data[h][yh] * b.data[yh][w];
            }
        }
    }

    return result;
}

// Transpose matrix
Matrix transpose(Matrix a) {
    Matrix result = {0};
    int i, j;

    // create matrix
    result = newMatrix(a.cols, a.rows, false);

    // swap a[r][c] with a[c][r]
    for (i = 0; i < a.rows; i++) {
        for (j = 0; j < a.cols; j++) {
            result.data[j][i] = a.data[i][j];
        }
    }

    return result;
}

// Extract the nth column of a matrix (1-indexed)
Matrix column(Matrix a, int n) {
    Matrix result = {0};
    int i, h;

    // verify dimensions
    if (n > a.cols || n < 1) {
        return result;
    }

    // create matrix
    result = newMatrix(a.rows, 1, false);

    // populate data
    for (h = 0; h < a.rows; h++) {
        result.data[h][0] = a.data[h][n-1];
    }

    return result;
}
