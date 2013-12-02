#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
  size_t width, height; // width, height
  double** data;        // pointer to the matrix
} Matrix;


double   norm(double x[], size_t length);
double*  dot_product(double x[], double y[]);
Matrix  transpose(Matrix input);
Matrix   subtract(Matrix x, Matrix y);
double*  max(double x[]);



double norm(double x[], size_t length) {
	double sum = 0;
	int i;

	for (i = 0; i < length; i++) {
		sum += x[i]*x[i];
	}

	return sqrt(sum);
}

Matrix subtract(Matrix x, Matrix y) {

	double** result;
	int i, h, w;
	Matrix matrix = {0};

	if (x.width != y.width || x.height != y.height) {
		return (Matrix){0};
	}

	result = malloc(sizeof(double*) * x.width);

	for (i = 0; i < x.height; i++) {
		result[i] = malloc(sizeof(double) * x.width);
	}

	for (h = 0; h < x.height; h++) {
		for (w = 0; w < x.width; w++) {
			result[h][w] = x.data[h][w] - y.data[h][w];
		}
	}

	matrix.width = x.width;
	matrix.height = x.height;
	matrix.data = result;

	return matrix;
}

Matrix array2Matrix(double* array, size_t arrayLen, size_t height, size_t width) {
	double** result;
	int i, h, w;
	Matrix matrix = {0};

	if (arrayLen != width * height) {
		return (Matrix){0};
	}

	// allocate new matrix
	result = malloc(sizeof(double*) * height);
	for (i = 0; i < height; i++) {
		result[i] = malloc(sizeof(double) * width);
	}

	// fill it in
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

Matrix transpose(Matrix input) {
	double** result;
	int i, j;
	Matrix matrix = {0};

	// allocate tranposed matrix
	result = malloc(sizeof(double*) * input.width);
	for (i = 0; i < input.width; i++) {
		result[i] = malloc(sizeof(double) * input.height);
	}

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

void print(Matrix m) {
	int i, j;

	printf("\n");
	for (i = 0; i < m.height; i++) {
		for (j = 0; j < m.width; j++) {
			printf("%f ", m.data[i][j]);
		}
		printf("\n");
	}
}


void main() {


	double test1[2][5] = {{1.0, 2.0, 3.0, 4.0, 5.0},
												{1.0, 4.0, 3.5, 4.0, 5.0}};

	double test2[2][5] = {{4.0, 2.0, 7.0, 1.0, 2.0},
												{1.6, 2.0, 3.0, 4.0, 5.6}};

	Matrix matrix1 = array2Matrix((double*)test1, 10, 2, 5);
	Matrix matrix2 = array2Matrix((double*)test2, 10, 2, 5);

	Matrix subtracted;
	Matrix transposed;

	int i, j, h, w;


	// Norm
	printf("Norm: %f\n\n", norm((double*)test1, 5));


	// Subtract
	printf("Subtract: ");
	subtracted = subtract(matrix1, matrix2);
	for (h = 0; h < 2; h++) {
		for (w = 0; w < 5; w++) {
			printf("%f ", subtracted.data[h][w]);
		}
	}
	printf("\n\n");


	// Transposed
	printf("Transpose: ");
	transposed = transpose(matrix1);
	for (i = 0; i < transposed.height; i++) {
		for (j = 0; j < transposed.width; j++) {
			printf("%f ", transposed.data[i][j]);
		}
		printf("\n");
	}



}
