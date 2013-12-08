//
// test.c
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
#include <float.h>
#include "test.h"
#include "matrix.h"
#include "face.h"

#define EE113D_DBL_EPSILON 1E-8 // DBL_EPSILON was too small

bool equals(double a, double b) {
    return fabs(a-b) <= EE113D_DBL_EPSILON;
}

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

    Matrix matrixA,
           matrixB,
           matrixC,
           matrixD,
           matrixE,
           matrixF,
           subtracted,
           dotProducted,
           transposed,
           columned;
    Pair   max;


    printf("Testing matrix functionality\n----------------------------\n");

    // Load into Matrix data type
    printf("Convert arrays to Matrix... ");
    matrixA = array2Matrix((double*)arrayA, 10, 2, 5);
    matrixB = array2Matrix((double*)arrayB, 10, 2, 5);
    matrixC = array2Matrix((double*)arrayC, 10, 5, 2);
    matrixD = array2Matrix((double*)arrayD, 5, 1, 5);
    matrixE = array2Matrix((double*)arrayE, 6, 6, 1);
    matrixF = array2Matrix((double*)arrayF, 5, 1, 5);
    printf("Done.\n");

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
    printf("Passed.\n");


    // Test norm
    printf("Testing norm()... ");
    assert(equals(vectorNorm(matrixD), sqrt(55.0)));
    assert(equals(vectorNorm(matrixE), sqrt(9.1e9)));
    assert(equals(vectorNorm(matrixF), vectorNorm(matrixD)));
    printf("Passed.\n");


    // Subtract
    printf("Testing subtract()... ");
    subtracted = subtract(matrixA, matrixB);
    assert(subtracted.rows == matrixA.rows);
    assert(subtracted.cols == matrixA.cols);
    assert(equals(subtracted.data[0][0], -3.0));
    assert(equals(subtracted.data[1][4], -0.6));
    assert(equals(sum(subtracted), 0.3));
    printf("Passed.\n");

    // Transposed
    printf("Testing transpose()... ");
    transposed = transpose(matrixB);
    assert(transposed.rows == matrixB.cols);
    assert(transposed.cols == matrixB.rows);
    assert(sum(matrixB) == sum(transposed));
    printf("Passed.\n");

    // DotProduct
    printf("Testing dotProduct()... ");
    dotProducted = dotProduct(matrixA, matrixC);
    assert(dotProducted.rows = matrixA.rows);
    assert(dotProducted.cols = matrixC.cols);
    assert(equals(dotProducted.data[0][0], 43.0));
    assert(equals(dotProducted.data[0][1], 58.6));
    assert(equals(dotProducted.data[1][0], 50.5));
    assert(equals(dotProducted.data[1][1], 64.1));
    printf("Passed.\n");

    // MaxWithIndex
    printf("Testing maxWithIndex()... ");
    max = maxWithIndex(matrixE);
    assert(equals(max.value, 60e3));
    assert(max.index == 5);

    columned = column(matrixC, 0);
    max = maxWithIndex(columned);
    assert(equals(max.value, 7.0));
    assert(max.index == 2);
    freeMatrix(&columned);

    columned = column(matrixC, 1);
    max = maxWithIndex(columned);
    assert(equals(max.value, 5.6));
    assert(max.index == 4);
    freeMatrix(&columned);
    printf("Passed.\n");

    // Column
    printf("Testing column()... ");
    columned = column(matrixA, 0);
    assert(columned.rows == matrixA.rows);
    assert(columned.cols == 1);
    assert(equals(sum(columned), 2.0));
    freeMatrix(&columned);

    columned = column(matrixA, 1);
    assert(columned.rows == matrixA.rows);
    assert(columned.cols == 1);
    assert(equals(sum(columned), 6.0));
    freeMatrix(&columned);

    columned = column(matrixA, 2);
    assert(columned.rows == matrixA.rows);
    assert(columned.cols == 1);
    assert(equals(sum(columned), 6.5));
    freeMatrix(&columned);

    columned = column(matrixC, 1);
    assert(columned.rows == matrixC.rows);
    assert(columned.cols == 1);
    assert(equals(sum(columned), 16.2));
    freeMatrix(&columned);

    columned = column(matrixE, 0);
    assert(columned.rows == matrixE.rows);
    assert(columned.cols == 1);
    assert(equals(sum(columned), 210e3));
    freeMatrix(&columned);
    printf("Passed.\n");

    // Free memory
    printf("Freeing matrix memory... ");
    freeMatrix(&matrixA);
    freeMatrix(&matrixB);
    freeMatrix(&matrixC);
    freeMatrix(&matrixD);
    freeMatrix(&matrixE);
    freeMatrix(&matrixF);

    freeMatrix(&subtracted);
    freeMatrix(&transposed);
    freeMatrix(&dotProducted);
    freeMatrix(&columned);
    printf("Done.\n");

    printf("\n");
}

void testFace() {
    double arrayA[2][5] = {{2.0, 3.0, 6.0, 7.0, 10.0},
                           {1.0, 4.0, 5.0, 8.0, 9.0}};

    double arrayB[2][1] = {{3.0},
                           {9.0}};

    double precomputedSimilar[5] = {1.0 / (1.0 + sqrt(65.0)),
                                    1.0 / (1.0 + sqrt(25.0)),
                                    1.0 / (1.0 + sqrt(25.0)),
                                    1.0 / (1.0 + sqrt(17.0)),
                                    1.0 / (1.0 + sqrt(49.0))};

    Matrix matrixA,
           matrixB,
           similar;


    printf("Testing face functionality\n----------------------------\n");

    // Load into Matrix data type
    printf("Convert arrays to Matrix... ");
    matrixA = array2Matrix((double*)arrayA, 10, 2, 5);
    matrixB = array2Matrix((double*)arrayB, 2, 2, 1);
    printf("Done.\n");


    // similarityScore()
    printf("Testing similarityScore()... ");
    similar = similarityScore(matrixA, matrixB, 5);
    assert(similar.rows == 5);
    assert(similar.cols == 1);
    assert(equals(similar.data[0][0], precomputedSimilar[0]));
    assert(equals(similar.data[1][0], precomputedSimilar[1]));
    assert(equals(similar.data[2][0], precomputedSimilar[2]));
    assert(equals(similar.data[3][0], precomputedSimilar[3]));
    assert(equals(similar.data[4][0], precomputedSimilar[4]));
    freeMatrix(&similar);
    printf("Passed.\n");

    // Free memory
    printf("Freeing matrix memory... ");
    freeMatrix(&matrixA);
    freeMatrix(&matrixB);
    printf("Done.\n");
}
