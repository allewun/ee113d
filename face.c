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
    subtracted = subtract(matrixA, matrixB);
    printMatrix(subtracted, 2);
    freeMatrix(&subtracted);
    printf("\n\n");

    // Transposed
    printf("Transpose:\n-------------------------------\n");

    printf("B =");
    printMatrix(matrixB, 2);
    printf("B' =");
    transposed = transpose(matrixB);
    printMatrix(transposed, 2);
    freeMatrix(&transposed);
    printf("\n\n");

    // DotProduct
    printf("Dot Product:\n-------------------------------\n");

    printf("A * B =");
    dotproducted = dotProduct(matrixA, matrixC);
    printMatrix(dotproducted, 2);
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
}
