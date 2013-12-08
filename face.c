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
#include "bmp.h"
#include "ee113d-data.txt"

#define EVECS_FILE    "evec_transposed.bmp"
#define MEANFACE_FILE "mean_face.bmp"

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


void genderDetection(char* file) {
    BITMAPINFOHEADER bmpInfoHeader;

    Matrix input_image,
           evectors,
           mean_face,
           faceMinusMean,
           featureVec,
           transposed_input_image,
           transposed_reshaped_input_image,
           similarity_score,
           features;
    double* bmpData;
    Pair maxIndex;

    features = array2Matrix((double*)featuresArray, 20*32, 20, 32);

    // load input_image
    bmpData = loadBitmapFileGrayscale(file, &bmpInfoHeader);
    input_image = array2Matrix((double*)bmpData, 180*200, 200, 180);
    free(bmpData);
    //printMatrix(input_image);

    // load mean_face
    bmpData = loadGrayBitmapFileGrayscale(MEANFACE_FILE, &bmpInfoHeader);
    mean_face = array2Matrix((double*)bmpData, 180*200, 36000, 1);
    free(bmpData);

    // load evectors
    evectors = array2Matrix((double*)evecs, 36000*20, 20, 36000);

    // transpose input_image
    transposed_input_image = transpose(input_image);
    freeMatrix(&input_image);

    // reshape input_image
    transposed_reshaped_input_image = reshape(transposed_input_image, 36000, 1);
    freeMatrix(&transposed_input_image);

    faceMinusMean = subtract(transposed_reshaped_input_image, mean_face);
    featureVec = dotProduct(evectors, faceMinusMean);

    // similarity score
    similarity_score = similarityScore(features, featureVec, 32);
    printMatrix(similarity_score);

    maxIndex = maxWithIndex(similarity_score);
    printf("Max = %f, index = %i\n\n", maxIndex.value, maxIndex.index);
}
