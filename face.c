//
// face.c
// Facial gender detection
//
//
// EE 113D - Fall 2013
//  * Allen Wu
//  * Bryant Khau
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "face.h"
#include "matrix.h"

double times2(double a) {
    return a*2;
}

void main() {

    double arrayA[2][5] = {{1.0, 2.0, 3.0, 4.0, 5.0},
                           {1.0, 4.0, 3.5, 4.0, 5.0}};

    double arrayB[2][5] = {{4.0, 2.0, 7.0, 1.0, 2.0},
                           {1.6, 2.0, 3.0, 4.0, 5.6}};

    double arrayC[5][2] = {{4.0, 1.6},
                           {2.0, 2.0},
                           {7.0, 3.0},
                           {1.0, 4.0},
                           {2.0, 5.6}};

    double arrayD[1][5] = {{1.0, 2.0, 3.0, 4.0, 5.0}};

    double arrayE[5][1] = {{1.0},
                           {2.0},
                           {3.0},
                           {4.0},
                           {5.0}};

    double arrayF[5] = {1.0, 2.0, 3.0, 4.0, 5.0};

    Matrix matrixA = array2Matrix((double*)arrayA, 10, 2, 5);
    Matrix matrixB = array2Matrix((double*)arrayB, 10, 2, 5);
    Matrix matrixC = array2Matrix((double*)arrayC, 10, 5, 2);
    Matrix matrixD = array2Matrix((double*)arrayD, 5, 5, 1);
    Matrix matrixE = array2Matrix((double*)arrayE, 5, 1, 5);
    Matrix matrixF = array2Matrix((double*)arrayF, 5, 1, 5);

    Matrix subtracted;
    Matrix dotproducted;
    Matrix transposed;
    Matrix columned;
    Matrix applied;

    int i, j, h, w;

    // Print matrices
    printf("===============================\n");
    printf("A =");
    printMatrix(matrixA, 2);
    printf("\n");

    printf("B =");
    printMatrix(matrixB, 2);
    printf("\n");

    printf("C =");
    printMatrix(matrixC, 2);
    printf("\n");

    printf("D =");
    printMatrix(matrixD, 2);
    printf("\n");

    printf("E =");
    printMatrix(matrixE, 2);
    printf("\n");

    printf("F =");
    printMatrix(matrixF, 2);
    printf("===============================\n\n\n");

    // Norm
    printf("Norm:\n-------------------------------\n");
    printf("  norm(A) = %f\n", vectorNorm(matrixA));
    printf("  norm(D) = %f\n", vectorNorm(matrixD));
    printf("  norm(E) = %f\n", vectorNorm(matrixE));
    printf("  norm(F) = %f\n", vectorNorm(matrixF));
    printf("\n\n");

    // Subtract
    printf("Subtract:\n-------------------------------\n");
    printf("A - B =");
    printMatrix(subtracted = subtract(matrixA, matrixB), 2);
    freeMatrix(&subtracted);
    printf("\n\n");

    // Transposed
    printf("Transpose:\n-------------------------------\n");
    printf("B =");
    printMatrix(matrixB, 2);
    printf("B' =");
    printMatrix(transposed = transpose(matrixB), 2);
    freeMatrix(&transposed);
    printf("\n\n");

    // DotProduct
    printf("Dot Product:\n-------------------------------\n");
    printf("A * B =");
    printMatrix(dotproducted = dotProduct(matrixA, matrixC), 2);
    freeMatrix(&dotproducted);
    printf("\n\n");

    // Max
    printf("Max:\n-------------------------------\n");
    printf("  max(A) = %f\n", max(matrixA));
    printf("  max(B) = %f\n", max(matrixB));
    printf("  max(C) = %f\n", max(matrixC));
    printf("  max(D) = %f\n", max(matrixD));
    printf("  max(E) = %f\n", max(matrixE));
    printf("  max(F) = %f\n", max(matrixF));
    printf("\n\n");

    // Column
    printf("Column:\n-------------------------------\n");
    printf("column(A, 1) =");
    printMatrix(columned = column(matrixA, 1), 2);

    printf("column(A, 2) =");
    printMatrix(columned = column(matrixA, 2), 2);

    printf("column(A, 3) =");
    printMatrix(columned = column(matrixA, 3), 2);

    printf("column(A, 4) =");
    printMatrix(columned = column(matrixA, 4), 2);

    printf("column(A, 5) =");
    printMatrix(columned = column(matrixA, 5), 2);

    printf("column(A, 6) =");
    printMatrix(columned = column(matrixA, 6), 2);

    printf("column(A, 0) =");
    printMatrix(columned = column(matrixA, 0), 2);
    freeMatrix(&columned);
    printf("\n\n");

    // matrixEach()
    printf("Matrix Each:\n-------------------------------\n");
    printf("matrixEach(times2, A) =");
    printMatrix(applied = matrixEach(times2, matrixA), 2);
}
