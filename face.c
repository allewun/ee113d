#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct {
  size_t width, height; // width, height
  double** data;        // pointer to the matrix
} Matrix;


double   norm(double x[], size_t length);
Matrix  dot_product(Matrix a, Matrix b);
Matrix  transpose(Matrix input);
Matrix  subtract(Matrix x, Matrix y);
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
    return matrix;
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
    return matrix;
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


Matrix dotproduct(Matrix m_x, Matrix m_y)
//double** dotproduct(double** x, double** y, size_t x_height, size_t x_width, size_t y_height, size_t y_width)
{
    Matrix m_result = {0};
  double** result;
  int i, h, w, yh;

  int x_width = m_x.width;
  int x_height = m_x.height;
  int y_width = m_y.width;
  int y_height = m_y.height;

  if (x_width != y_height) {
    // dimension mismatch
    return m_result;
  }

  // allocate new matrix
  result = calloc(x_height, sizeof(double*));
  for (i = 0; i < x_height; i++) {
    result[i] = calloc(y_width, sizeof(double));
  }

  // fill it in
  for (h = 0; h < x_height; h++)
  {
    for (w = 0; w < y_width; w++)
    {
      for (yh = 0; yh < y_height; yh++)
      {
        result[h][w] += m_x.data[h][yh] * m_y.data[yh][w];
		printf("result[%i][%i]=(%f)\n", h, w, result[h][w] );
		printf("matrix1[%i][%i]=(%f)\n", h, yh, m_x.data[h][yh] );
		printf("matrix2[%i][%i]=(%f)\n", yh, w, m_y.data[yh][w] );
      }

    }
  }

  m_result.width = y_width;
  m_result.height = x_height;
  m_result.data = result;
  return m_result;
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
	  //printf("%f ", result[j][i]);
    }
  }

  matrix.width = input.height;
  matrix.height = input.width;
  matrix.data = result;

  //printMatrix(matrix);

  return matrix;
}



void main() {


  double test1[2][5] = {{1.0, 2.0, 3.0, 4.0, 5.0},
                        {1.0, 4.0, 3.5, 4.0, 5.0}};

  double test2[2][5] = {{4.0, 2.0, 7.0, 1.0, 2.0},
                          {1.6, 2.0, 3.0, 4.0, 5.6}};

  double test2_transposed[5][2] = {{4.0, 1.6},
                                   {2.0,2.0},
                                   {7.0,3.0},
                                   {1.0,4.0},
                                   {2.0,5.6}};

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
