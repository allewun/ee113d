#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double   norm(double x[], size_t length);
double*  dot_product(double x[], double y[]);
double*  transpose(double x[], size_t width, size_t height);
double** subtract(double **x, double **y, size_t height, size_t width);
double*  max(double x[]);


double norm(double x[], size_t length) {
	double sum = 0;

	for (int i = 0; i < length; i++) {
		sum += x[i]*x[i];
	}

	return sqrt(sum);
}

double** subtract(double** x, double** y, size_t height, size_t width) {

	double** result = malloc(sizeof(double*) * height);
	int i, h, w;


	for (i = 0; i < height; i++) {
		result[i] = malloc(sizeof(double) * width);
	}

	for (h = 0; h < height; h++) {
		for (w = 0; w < width; w++) {
			result[h][w] = x[h][w] - y[h][w];
		}
	}

	return result;
}

double** array2Matrix(double* array, size_t arrayLen, size_t height, size_t width) {
	double** result;
	int i, h, w;

	if (arrayLen != width * height) {
		return NULL;
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

	return result;
}


void main() {


	double test1[2][5] = {{1.0, 2.0, 3.0, 4.0, 5.0},
												{1.0, 4.0, 3.5, 4.0, 5.0}};

	double test2[2][5] = {{4.0, 2.0, 7.0, 1.0, 2.0},
												{1.6, 2.0, 3.0, 4.0, 5.6}};

	double** matrix1 = array2Matrix((double*)test1, 10, 2, 5);
	double** matrix2 = array2Matrix((double*)test2, 10, 2, 5);

	double** subtracted;

	int i, h, w;



	// Norm
	printf("Norm: %f\n\n", norm((double*)test1, 5));


	// Subtract
	printf("Subtract: ");
	subtracted = subtract(matrix1, matrix2, 2, 5);
	for (h = 0; h < 2; h++) {
		for (w = 0; w < 5; w++) {
			printf("%f ", subtracted[h][w]);
		}
	}
	printf("\n\n");
}
