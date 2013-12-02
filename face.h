//=============================================================================
// face.h
//=============================================================================


// Matrix data type
typedef struct {
  size_t width, height;
  double** data;
} Matrix;

// Helper functions
Matrix array2Matrix(double* array, size_t arrayLen, size_t height, size_t width);
void printMatrix(Matrix m);

// Matrix/vector functions
double  norm(double x[], size_t length);
Matrix  dot_product(Matrix a, Matrix b);
Matrix  transpose(Matrix input);
Matrix  subtract(Matrix x, Matrix y);
double* max(double x[]);
