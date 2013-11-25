#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double  norm(double x[], size_t length);
double* dot_product(double x[], double y[]);
double* transpose(double x[], size_t width, size_t height);
double** subtract(double **x, double **y, size_t height, size_t width);
double* max(double x[]);


double norm(double x[], size_t length) {
  double sum = 0;

  for (int i = 0; i < length; i++) {
    sum += x[i]*x[i];
  }

  return sqrt(sum);
}

double** subtract(double** x, double** y, size_t height, size_t width) {

  double** result = malloc(sizeof(double*) * height);


  for (int i = 0; i < height; i++) {
    result[i] = malloc(sizeof(double) * width);
  }

  for (int h = 0; h < height; h++) {
    for (int w = 0; w < width; w++) {
      result[h][w] = x[h][w] - y[h][w];
    }
  }

  return result;
}

double** array2Matrix(double* array, size_t arrayLen, size_t height, size_t width) {
  if (arrayLen != width * height) {
    return NULL;
  }

  // allocate new matrix
  double** result = malloc(sizeof(double*) * height);
  for (int i = 0; i < height; i++) {
    result[i] = malloc(sizeof(double) * width);
  }

  // fill it in
  for (int h = 0; h < height; h++) {
    for (int w = 0; w < width; w++) {
      result[h][w] = array[h*width + w];
    }
  }

  return result;
}

// double* transpose(double x[], size_t width, size_t height) {

// }

int main() {


  double test1[2][5] = {{1.0, 2.0, 3.0, 4.0, 5.0},
                        {1.0, 4.0, 3.5, 4.0, 5.0}};

  double test2[2][5] = {{4.0, 2.0, 7.0, 1.0, 2.0},
                        {1.6, 2.0, 3.0, 4.0, 5.6}};

  double** matrix1 = array2Matrix(test1, 10, 2, 5);
  double** matrix2 = array2Matrix(test2, 10, 2, 5);

  // Norm
  printf("Norm: %f\n\n", norm(test1, 5));


  // Subtract
  printf("Subtract: ");
  double** subtracted = subtract(matrix1, matrix2, 2, 5);
  for (int h = 0; h < 2; h++) {
    for (int w = 0; w < 5; w++) {
      printf("%f ", subtracted[h][w]);
    }
  }
  printf("\n\n");


 // return 0;

}



// [1, 2, 3, 4,5 ,6]

// p = [a = [2,3,4],[4,5,7]]

// p -> a -> 2