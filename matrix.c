//
// matrix.c
// Facial gender detection
//
//
// EE 113D - Fall 2013
//  * Allen Wu
//  * Bryant Khau
//

#include "matrix.h"

#define DEFAULT_FLOAT_DECIMALS 6


//=============================================================================
// Helper functions
//=============================================================================

Matrix array2Matrix(double* array, size_t arrayLen, size_t height, size_t width) {
    double** result;
    Matrix matrix = {0};
    int i, h, w;

    // verify dimensions
    if (arrayLen != width * height) {
        return matrix;
    }

    // allocate memory
    result = malloc(sizeof(double*) * height);
    for (i = 0; i < height; i++) {
        result[i] = malloc(sizeof(double) * width);
    }

    // populate data
    for (h = 0; h < height; h++) {
        for (w = 0; w < width; w++) {
            result[h][w] = array[h*width + w];
        }
    }

    matrix.width = width;
    matrix.height = height;
    matrix.data = result;

    return matrix;
}

void printMatrix(Matrix m, int decimals) {
    int i, j;
    if (decimals == -1) {
        decimals = DEFAULT_FLOAT_DECIMALS;
    }

    printf("\n");
    if (m.width == 0 || m.height == 0) {
        printf("[]");
        return;
    }
    for (i = 0; i < m.height; i++) {
        for (j = 0; j < m.width; j++) {
            if (i == 0 && j == 0) {
                printf("[ ");
            }
            else if (j == 0) {
                printf("  ");
            }
            printf("%.*f ", decimals, m.data[i][j]);
        }
        if (i == m.height - 1) {
            printf("]");
        }
        printf("\n");
    }
}

void freeMatrix(Matrix* m) {
    int i;
    for (i = 0; i < m->height; i++) {
        free(m->data[i]);
    }
    free(m->data);

    m->width = 0;
    m->height = 0;
    m->data = NULL;
}

//=============================================================================
// Matrix/vector functions
//=============================================================================

// Calculate vector norm
double vectorNorm(Matrix a) {
    double sum = 0;
    int i, j;

    // calculate vector norm if matrix is a vector
    if (a.width == 1) {
        for (i = 0; i < a.height; i++) {
            sum += a.data[i][0] * a.data[i][0];
        }
    }
    else if (a.height == 1) {
        for (i = 0; i < a.width; i++) {
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

// Perform matrix subtraction
Matrix subtract(Matrix a, Matrix b) {
    double** result;
    Matrix matrix = {0};
    int i, h, w;

    // verify dimensions
    if (a.width != b.width || a.height != b.height) {
        return matrix;
    }

    // allocate memory
    result = malloc(sizeof(double*) * a.width);
    for (i = 0; i < a.height; i++) {
        result[i] = malloc(sizeof(double) * a.width);
    }

    // subtract
    for (h = 0; h < a.height; h++) {
        for (w = 0; w < a.width; w++) {
            result[h][w] = a.data[h][w] - b.data[h][w];
        }
    }

    matrix.width = a.width;
    matrix.height = a.height;
    matrix.data = result;

    return matrix;
}

// Perform matrix dot product
Matrix dotProduct(Matrix a, Matrix b) {
    double** result;
    Matrix matrix = {0};

    int i, h, w, yh;

    // verify dimensions
    if (a.width != b.height) {
        return matrix;
    }

    // allocate new matrix
    result = calloc(a.height, sizeof(double*));
    for (i = 0; i < a.height; i++) {
        result[i] = calloc(b.width, sizeof(double));
    }

    // dot product
    for (h = 0; h < a.height; h++) {
        for (w = 0; w < b.width; w++) {
            for (yh = 0; yh < b.height; yh++) {
                result[h][w] += a.data[h][yh] * b.data[yh][w];
            }
        }
    }

    matrix.width = b.width;
    matrix.height = a.height;
    matrix.data = result;

    return matrix;
}

// Transpose matrix
Matrix transpose(Matrix input) {
    double** result;
    Matrix matrix = {0};
    int i, j;

    // allocate tranposed matrix
    result = malloc(sizeof(double*) * input.width);
    for (i = 0; i < input.width; i++) {
        result[i] = malloc(sizeof(double) * input.height);
    }

    // swap m[r][c] with m[c][r]
    for (i = 0; i < input.height; i++) {
        for (j = 0; j < input.width; j++) {
            result[j][i] = input.data[i][j];
        }
    }

    matrix.width = input.height;
    matrix.height = input.width;
    matrix.data = result;

    return matrix;
}

// Find max element of matrix
double max(Matrix a) {
    double currentMax = -DBL_MAX;
    int i, j;

    for (i = 0; i < a.height; i++) {
        for (j = 0; j < a.width; j++) {
            if (a.data[i][j] > currentMax) {
                currentMax = a.data[i][j];
            }
        }
    }

    return currentMax;
}

// Extract the nth column of a matrix (1-indexed)
Matrix column(Matrix a, int n) {
    double** result;
    Matrix matrix = {0};
    int i, h;

    // verify dimensions
    if (n > a.width || n < 1) {
        return matrix;
    }

    // allocate memory
    result = malloc(sizeof(double*) * a.height);
    for (i = 0; i < a.height; i++) {
        result[i] = malloc(sizeof(double));
    }

    // populate data
    for (h = 0; h < a.height; h++) {
        result[h][0] = a.data[h][n-1];
    }

    matrix.width = 1;
    matrix.height = a.height;
    matrix.data = result;

    return matrix;
}
