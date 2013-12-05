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


//=============================================================================
// Helper functions
//=============================================================================

Matrix array2Matrix(double* array, size_t arrayLen, size_t rows, size_t cols) {
    double** result;
    Matrix matrix = {0};
    int i, h, w;

    // verify dimensions
    if (arrayLen != cols * rows) {
        return matrix;
    }

    // allocate memory
    result = mallocMatrix(rows, cols);

    // populate data
    for (h = 0; h < rows; h++) {
        for (w = 0; w < cols; w++) {
            result[h][w] = array[h*cols + w];
        }
    }

    matrix.cols = cols;
    matrix.rows = rows;
    matrix.data = result;

    return matrix;
}

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

double** mallocMatrix(size_t rows, size_t cols) {
    double** result;
    int i;

    result = malloc(sizeof(double*) * rows);
    for (i = 0; i < rows; i++) {
        result[i] = malloc(sizeof(double) * cols);
    }

    return result;
}

double** callocMatrix(size_t rows, size_t cols) {
    double** result;
    int i;

    result = calloc(rows, sizeof(double*));
    for (i = 0; i < rows; i++) {
        result[i] = calloc(cols, sizeof(double));
    }

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

// Perform matrix subtraction
Matrix subtract(Matrix a, Matrix b) {
    double** result;
    Matrix matrix = {0};
    int i, h, w;

    // verify dimensions
    if (a.cols != b.cols || a.rows != b.rows) {
        return matrix;
    }

    // allocate memory
    result = mallocMatrix(a.rows, a.cols);

    // subtract
    for (h = 0; h < a.rows; h++) {
        for (w = 0; w < a.cols; w++) {
            result[h][w] = a.data[h][w] - b.data[h][w];
        }
    }

    matrix.cols = a.cols;
    matrix.rows = a.rows;
    matrix.data = result;

    return matrix;
}

// Perform matrix dot product
Matrix dotProduct(Matrix a, Matrix b) {
    double** result;
    Matrix matrix = {0};
    int i, h, w, yh;

    // verify dimensions
    if (a.cols != b.rows) {
        return matrix;
    }

    // allocate new matrix
    result = callocMatrix(a.rows, a.cols);

    // dot product
    for (h = 0; h < a.rows; h++) {
        for (w = 0; w < b.cols; w++) {
            for (yh = 0; yh < b.rows; yh++) {
                result[h][w] += a.data[h][yh] * b.data[yh][w];
            }
        }
    }

    matrix.cols = b.cols;
    matrix.rows = a.rows;
    matrix.data = result;

    return matrix;
}

// Transpose matrix
Matrix transpose(Matrix a) {
    double** result;
    Matrix matrix = {0};
    int i, j;

    // allocate tranposed matrix
    result = mallocMatrix(a.cols, a.rows);

    // swap a[r][c] with a[c][r]
    for (i = 0; i < a.rows; i++) {
        for (j = 0; j < a.cols; j++) {
            result[j][i] = a.data[i][j];
        }
    }

    matrix.cols = a.rows;
    matrix.rows = a.cols;
    matrix.data = result;

    return matrix;
}

// Find max element of matrix
double max(Matrix a) {
    double currentMax = -DBL_MAX;
    int i, j;

    for (i = 0; i < a.rows; i++) {
        for (j = 0; j < a.cols; j++) {
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
    if (n > a.cols || n < 1) {
        return matrix;
    }

    // allocate memory
    result = mallocMatrix(a.rows, 1);

    // populate data
    for (h = 0; h < a.rows; h++) {
        result[h][0] = a.data[h][n-1];
    }

    matrix.cols = 1;
    matrix.rows = a.rows;
    matrix.data = result;

    return matrix;
}


// Apply a function to each element of matrix a
Matrix matrixEach(double (*function)(), Matrix a) {
    double** result;
    Matrix matrix = {0};
    int i, j;

    // allocate memory
    result = mallocMatrix(a.rows, a.cols);

    // apply function
    for (i = 0; i < a.rows; i++) {
        for (j = 0; j < a.cols; j++) {
            result[i][j] = function(a.data[i][j]);
        }
    }

    matrix.cols = a.cols;
    matrix.rows = a.rows;
    matrix.data = result;

    return matrix;
}
