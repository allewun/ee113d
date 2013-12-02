//=============================================================================
// face.c
//=============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "face.h"



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

void printMatrix(Matrix m) {
	int i, j;

	printf("\n");
	for (i = 0; i < m.height; i++) {
		for (j = 0; j < m.width; j++) {
			if (i == 0 && j == 0) {
				printf("[ ");
			}
			else if (j == 0) {
				printf("  ");
			}
			printf("%f ", m.data[i][j]);
		}
		if (i == m.height - 1) {
			printf("]");
		}
		printf("\n");
	}
}


//=============================================================================
// Matrix/vector functions
//=============================================================================

double norm(double x[], size_t length) {
	double sum = 0;
	int i;

	for (i = 0; i < length; i++) {
		sum += x[i]*x[i];
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
Matrix dotproduct(Matrix a, Matrix b) {
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



void main() {

	double test1[2][5] = {{1.0, 2.0, 3.0, 4.0, 5.0},
						  {1.0, 4.0, 3.5, 4.0, 5.0}};

	double test2[2][5] = {{4.0, 2.0, 7.0, 1.0, 2.0},
						  {1.6, 2.0, 3.0, 4.0, 5.6}};

	double test2_transposed[5][2] = {{4.0, 1.6},
									 {2.0, 2.0},
									 {7.0, 3.0},
									 {1.0, 4.0},
									 {2.0, 5.6}};

	Matrix matrix2_tranp = array2Matrix((double*)test2_transposed, 10, 5, 2);
	Matrix matrix2_allen;

	Matrix matrix1 = array2Matrix((double*)test1, 10, 2, 5);
	Matrix matrix2 = array2Matrix((double*)test2, 10, 2, 5);

	Matrix subtracted;
	Matrix dotproducted;
	Matrix transposed;

	int i, j, h, w;



	// Norm
	printf("Norm: %f\n\n", norm((double*)test1, 5));

	// Subtract
	printf("Subtract: ");
	subtracted = subtract(matrix1, matrix2);
	printMatrix(subtracted);
	printf("\n\n");

	// Transposed
	printf("Transpose: ");
	printf("Transpose(matrix2): ");
	printMatrix(matrix2);
	transposed = transpose(matrix2);
	printMatrix(transposed);
	printf("\n\n");

	// DotProduct
	printf("Dot Product: ");
	matrix2_allen = transpose(matrix2);
	free(matrix2_allen.data);
	printf("matrix1: ");
	printMatrix(matrix1);
	printf("matrix2: ");
	printMatrix(matrix2_tranp);
	dotproducted = dotproduct(matrix1, matrix2_tranp );
	printMatrix(dotproducted);
	printf("\n\n");
}
