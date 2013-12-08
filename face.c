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
#include "face.h"
#include "bmp.h"
#include "ee113d-data.txt"

#define IMAGE_WIDTH    180
#define IMAGE_HEIGHT   200
#define IMAGE_SIZE     (IMAGE_WIDTH * IMAGE_HEIGHT)
#define IMAGE_COUNT    32
#define NUM_EIGENFACES 20

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
    float* bmpData;
    Pair maxIndex;

    printf("Facial gender detection for %s \n----------------------------\n", file);


    printf("Loading input image...\n");
    // load input_image
    bmpData = loadBitmapFileGrayscaleOutput(file, &bmpInfoHeader, false);
    input_image = array2Matrix((float*)bmpData, IMAGE_SIZE, IMAGE_HEIGHT, IMAGE_WIDTH);
    free(bmpData);

    printf("Transposing input image...\n");
    // transpose input_image
    transposed_input_image = transpose(input_image);
    freeMatrix(&input_image);

    printf("Reshaping input image...\n");
    // reshape input_image
    transposed_reshaped_input_image = reshape(transposed_input_image, IMAGE_SIZE, 1);
    freeMatrix(&transposed_input_image);

    printf("Calculating eigenfaces...\n");
    // load evectors
    evectors = array2Matrix((float*)evecs, IMAGE_SIZE * NUM_EIGENFACES, NUM_EIGENFACES, IMAGE_SIZE);

    printf("Calculating mean face...\n");
    // load mean_face
    bmpData = loadBitmapFileGrayscaleOutput(MEANFACE_FILE, &bmpInfoHeader, true);
    mean_face = array2Matrix((float*)bmpData, IMAGE_SIZE, IMAGE_SIZE, 1);
    free(bmpData);

    printf("Calculating face differences...\n");
    faceMinusMean = subtract(transposed_reshaped_input_image, mean_face);
    freeMatrix(&transposed_reshaped_input_image);
    freeMatrix(&mean_face);

    printf("Projecting facial features onto eigenfaces...\n");
    featureVec = dotProduct(evectors, faceMinusMean);
    freeMatrix(&faceMinusMean);

    printf("Analyzing face matches...\n");
    // similarity score
    features = array2Matrix((float*)featuresArray, NUM_EIGENFACES * IMAGE_COUNT, NUM_EIGENFACES, IMAGE_COUNT);
    similarity_score = similarityScore(features, featureVec, IMAGE_COUNT);
    printMatrix(similarity_score);

    maxIndex = maxWithIndex(similarity_score);
    printf("Max = %f, index = %i\n\n", maxIndex.value, maxIndex.index);

    printf("Determining gender...\n");
}
