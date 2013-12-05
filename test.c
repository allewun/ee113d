//
// test.c
// Facial gender detection
//
//
// EE 113D - Fall 2013
//  * Allen Wu
//  * Bryant Khau
//

#include <assert.h>

#include "face.h"
#include "matrix.h"


void testMatrix() {
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

    double arrayE[6][1] = {{10e3},
                           {20e3},
                           {30e3},
                           {40e3},
                           {50e3},
                           {60e3}};

    double arrayF[5] = {1.0, 2.0, 3.0, 4.0, 5.0};

    // Load into Matrix data type
    printf("Convert arrays to Matrix... ");
    Matrix matrixA = array2Matrix((double*)arrayA, 10, 2, 5);
    Matrix matrixB = array2Matrix((double*)arrayB, 10, 2, 5);
    Matrix matrixC = array2Matrix((double*)arrayC, 10, 5, 2);
    Matrix matrixD = array2Matrix((double*)arrayD, 5, 1, 5);
    Matrix matrixE = array2Matrix((double*)arrayE, 6, 6, 1);
    Matrix matrixF = array2Matrix((double*)arrayF, 5, 1, 5);
    printf("Done.\n");

    Matrix subtracted;
    Matrix dotproducted;
    Matrix transposed;
    Matrix columned;


    // Test proper loading into Matrix data type
    printf("Testing proper loading... ");
    assert(matrixA.rows == 2);
    assert(matrixA.cols == 5);
    assert(matrixA.data[1][2] == arrayA[1][2]);

    assert(matrixB.rows == 2);
    assert(matrixB.cols == 5);
    assert(matrixB.data[1][4] == arrayB[1][4]);

    assert(matrixC.rows == 5);
    assert(matrixC.cols == 2);
    assert(matrixC.data[0][0] == arrayC[0][0]);

    assert(matrixD.rows == 1);
    assert(matrixD.cols == 5);
    assert(matrixD.data[0][2] == arrayD[0][2]);

    assert(matrixE.rows == 6);
    assert(matrixE.cols == 1);
    assert(matrixE.data[5][0] == arrayE[5][0]);

    assert(matrixF.rows == 1);
    assert(matrixF.cols == 5);
    assert(matrixF.data[0][2] == arrayF[2]);
    printf("Done.\n");


    // Test norm
    printf("Testing norm()... ");
    assert(equals(vectorNorm(matrixD), sqrt(55.0)));
    assert(equals(vectorNorm(matrixE), sqrt(9.1e9)));
    assert(equals(vectorNorm(matrixF), vectorNorm(matrixD)));
    printf("Done.\n");


    // Subtract
    printf("Testing subtract()... ");
    subtracted = subtract(matrixA, matrixB);
    assert(subtracted.rows == matrixA.rows);
    assert(subtracted.cols == matrixA.cols);
    assert(equals(subtracted.data[0][0], -3.0));
    assert(equals(subtracted.data[1][4], -0.6));
    assert(equals(sum(subtracted), 0.3));
    printf("Done.\n");

    // Transposed
    printf("Testing transpose()... ");
    transposed = transpose(matrixB);
    assert(transposed.rows == matrixB.cols);
    assert(transposed.cols == matrixB.rows);
    assert(sum(matrixB) == sum(transposed));
    printf("Done.\n");

    // DotProduct
    printf("Testing dotProduct()... ");
    dotproducted = dotProduct(matrixA, matrixC);
    assert(dotproducted.rows = matrixA.rows);
    assert(dotproducted.cols = matrixC.cols);
    assert(equals(dotproducted.data[0][0], 43.0));
    assert(equals(dotproducted.data[0][1], 58.6));
    assert(equals(dotproducted.data[1][0], 50.5));
    assert(equals(dotproducted.data[1][1], 64.1));
    printf("Done.\n");

    // Max
    printf("Testing max()... ");
    assert(equals(max(matrixA), 5.0));
    assert(equals(max(matrixB), 7.0));
    assert(equals(max(matrixC), 7.0));
    assert(equals(max(matrixD), 5.0));
    assert(equals(max(matrixE), 60e3));
    assert(equals(max(matrixF), 5.0));
    printf("Done.\n");

    // Column
    printf("Testing column()... ");
    columned = column(matrixA, 1);
    assert(columned.rows == matrixA.rows);
    assert(columned.cols == 1);
    assert(equals(sum(columned), 2.0));
    freeMatrix(&columned);

    columned = column(matrixA, 2);
    assert(columned.rows == matrixA.rows);
    assert(columned.cols == 1);
    assert(equals(sum(columned), 6.0));
    freeMatrix(&columned);

    columned = column(matrixA, 3);
    assert(columned.rows == matrixA.rows);
    assert(columned.cols == 1);
    assert(equals(sum(columned), 6.5));
    freeMatrix(&columned);

    columned = column(matrixC, 2);
    assert(columned.rows == matrixC.rows);
    assert(columned.cols == 1);
    assert(equals(sum(columned), 16.2));
    freeMatrix(&columned);

    columned = column(matrixE, 1);
    assert(columned.rows == matrixE.rows);
    assert(columned.cols == 1);
    assert(equals(sum(columned), 210e3));
    freeMatrix(&columned);
    printf("Done.\n");

    // Free memory
    freeMatrix(&matrixA);
    freeMatrix(&matrixB);
    freeMatrix(&matrixC);
    freeMatrix(&matrixD);
    freeMatrix(&matrixE);
    freeMatrix(&matrixF);

    freeMatrix(&subtracted);
    freeMatrix(&transposed);
    freeMatrix(&dotproducted);
    freeMatrix(&columned);
}