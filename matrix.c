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

#define PRINT_MATRIX_DECIMALS 4

//=============================================================================
// Helper functions
//=============================================================================

// Convert a plain array to a Matrix struct
Matrix array2Matrix(float* array, size_t arrayLen, size_t rows, size_t cols) {
    Matrix result = {0};
    int r, c;

    // verify dimensions
    if (arrayLen != cols * rows) {
        return result;
    }

    // create matrix
    result = newMatrix(rows, cols, false);

    // populate data
    for (r = 0; r < rows; r++) {
        for (c = 0; c < cols; c++) {
            result.data[r][c] = array[r*cols + c];
        }
    }

    return result;
}

// Print matrix to console
void printMatrix(Matrix matrix) {
    int r, c;

    printf("\n");
    if (matrix.cols == 0 || matrix.rows == 0) {
        printf("[]\n");
        return;
    }
    for (r = 0; r < matrix.rows; r++) {
        for (c = 0; c < matrix.cols; c++) {
            if (r == 0 && c == 0) {
                printf("[ ");
            }
            else if (c == 0) {
                printf("  ");
            }
            printf("%.*f, ", PRINT_MATRIX_DECIMALS, matrix.data[r][c]);
        }
        if (r == matrix.rows - 1) {
            printf("]");
        }
        printf("\n");
    }
}

// Free memory allocated for matrix data
void freeMatrix(Matrix* matrix) {
    int i;
    for (i = 0; i < matrix->rows; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);

    matrix->cols = 0;
    matrix->rows = 0;
    matrix->data = NULL;
}

// Allocate an rxc block of memory to be used for a matrix
Matrix newMatrix(size_t rows, size_t cols, bool clearMemory) {
    Matrix result = {0};
    float** data;
    int i;

    data = clearMemory ? calloc(rows, sizeof(float*)) : malloc(sizeof(float*) * rows);

    if (data == NULL) {
        printf("New matrix memory allocation failure!\n");
        return result;
    }

    for (i = 0; i < rows; i++) {
        data[i] = clearMemory ? calloc(cols, sizeof(float)) : malloc(sizeof(float) * cols);

        if (data[i] == NULL) {
            printf("New row {%i} memory allocation failure!\n");
            return result;
        }
    }

    result.data = data;
    result.rows = rows;
    result.cols = cols;

    //printf("NEW MATRIX [%i x %i]\n", rows, cols);

    return result;
}


//=============================================================================
// Matrix/vector functions
//=============================================================================

// Calculate vector norm
float vectorNorm(Matrix a) {
    float sum = 0.0;
    int i;

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
Pair maxWithIndex(Matrix matrix) {
    float currentMax = -DBL_MAX;
    int currentIndex = -1;
    Pair result = {-1, -1};

    int r, c, rMax, cMax;

    if (matrix.rows == 1) {
        rMax = 1;
        cMax = matrix.cols;
    }
    else if (matrix.cols == 1) {
        rMax = matrix.rows;
        cMax = 1;
    }
    else {
        return result;
    }

    for (r = 0; r < rMax; r++) {
        for (c = 0; c < cMax; c++) {
            if (matrix.data[r][c] > currentMax) {
                currentMax   = matrix.data[r][c];
                currentIndex = r+c;
            }
        }
    }

    result.value = currentMax;
    result.index = currentIndex;

    return result;
}

// Sum of all elements of matrix
float sum(Matrix a) {
    float result = 0.0;
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
    int r, c;

    // verify dimensions
    if (a.cols != b.cols || a.rows != b.rows) {
        return result;
    }

    // create matrix
    result = newMatrix(a.rows, a.cols, false);

    // subtract
    for (r = 0; r < a.rows; r++) {
        for (c = 0; c < a.cols; c++) {
            result.data[r][c] = a.data[r][c] - b.data[r][c];
        }
    }

    return result;
}

// Perform matrix dot product
Matrix dotProduct(Matrix a, Matrix b) {
    Matrix result = {0};
    int h, w, yh;

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
    int r, c;

    // create matrix
    result = newMatrix(a.cols, a.rows, false);

    // swap a[r][c] with a[c][r]
    for (r = 0; r < a.rows; r++) {
        for (c = 0; c < a.cols; c++) {
            result.data[c][r] = a.data[r][c];
        }
    }

    return result;
}

// Extract the nth column of a matrix
Matrix column(Matrix a, int n) {
    Matrix result = {0};
    int r;

    // verify dimensions
    if (n > a.cols-1 || n < 0) {
        return result;
    }

    // create matrix
    result = newMatrix(a.rows, 1, false);

    // populate data
    for (r = 0; r < a.rows; r++) {
        result.data[r][0] = a.data[r][n];
    }

    return result;
}

Matrix reshape(Matrix m, int r, int c) {
    Matrix result = {0};
    int x, y, i = 0;


    if (r*c != m.rows*m.cols) {
        printf("Reshape dimension mismatch!\n");
        return result;
    }

    // create matrix
    result = newMatrix(r, c, false);

    // populate
    for (y = 0; y < m.rows; y++) {
        for (x = 0; x < m.cols; x++) {
            i = y*m.cols + x;
            result.data[i/c][i%c] = m.data[y][x];
        }
    }

    return result;
}
