//
// face.c
// Facial gender detection
//
//
// EE 113D - Fall 2013
//  * Allen Wu
//  * Bryant Khau
//

#include "face.h"

Matrix similarityScore(Matrix features, Matrix featureVector, int n) {
    Matrix result = newMatrix(n, 1, false);
    Matrix featuresCol = {0};
    Matrix difference = {0};
    int i;

    for (i = 0; i < n; i++) {
        featuresCol = column(features, i);
        difference = subtract(featuresCol, featureVector);

        result.data[i][0] = 1 / (1 + vectorNorm(difference));

        freeMatrix(&featuresCol);
        freeMatrix(&difference);
    }

    return result;
}
