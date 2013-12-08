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

#define MEANFACE_FILE "mean_face.bmp"

// 0-32 = male, 33-(NUM_IMAGES - 1) = female
#define GENDER_CUTOFF_INDEX 33

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
    Pair maxIndex1, maxIndex2, maxIndex3;
    float genderWeight1, genderWeight2, genderWeight3;

    char* raceTable[] = {"French", "Iraqi", "Irish", "Isreali", "Mexican", "Mongolian", "Peruvian", "Polish", "Puerto Rican", "Uzbekistani", "African-American", "White American", "Chinese", "Romanian", "Russian", "Samoan", "Saudi Arabian", "Czech", "Hungarian", "Italian", "Serbian", "South African", "South Indian", "Spanish", "Korean", "Thai", "Brazilian", "Swiss", "Taiwanese", "Tibetan", "Ukrainian", "Vietnamese", "West African",
                         "Uzbekistani", "Welsh", "West African", "Vietnamese", "Chinese", "Hungarian", "Puerto Rican", "Thai", "African-American", "Afghan", "South African", "Cambodian", "English", "Ethiopian", "Filipino", "Finnish", "German", "Greek", "North Indian", "Iranian", "Irish", "Israeli", "Italian", "Mongolian", "Peruvian", "Polish", "Romanian", "South Indian", "Spanish", "Swedish", "Swiss", "Taiwanese", "Dutch", "Serbian", "Turkish", "Lebanese", "Brazilian"};

    printf("Facial gender detection for %s \n--------------------------------------\n", file);


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
    features = array2Matrix((float*)featuresArray, NUM_EIGENFACES * NUM_IMAGES, NUM_EIGENFACES, NUM_IMAGES);
    similarity_score = similarityScore(features, featureVec, NUM_IMAGES);
    //printMatrix(similarity_score);

    maxIndex1 = maxWithIndex(similarity_score);
    similarity_score.data[maxIndex1.index][0] = 0;

    maxIndex2 = maxWithIndex(similarity_score);
    similarity_score.data[maxIndex2.index][0] = 0;

    maxIndex3 = maxWithIndex(similarity_score);
    similarity_score.data[maxIndex3.index][0] = 0;

    printf("Determining gender...\n");

    genderWeight1 = ((maxIndex1.index >= GENDER_CUTOFF_INDEX) ? -1.0 : 1.0) * maxIndex1.value;
    genderWeight2 = ((maxIndex1.index >= GENDER_CUTOFF_INDEX) ? -1.0 : 1.0) * maxIndex2.value;
    genderWeight3 = ((maxIndex1.index >= GENDER_CUTOFF_INDEX) ? -1.0 : 1.0) * maxIndex3.value;

    printf("==> ");
    if (genderWeight1 + genderWeight2 + genderWeight3 >= 0) {
        printf("[MALE]");
    }
    else {
        printf("[FEMALE]");
    }
    printf(" : %.3f %s (%s), %.3f %s (%s), %.3f %s (%s)", maxIndex1.value, ((maxIndex1.index >= GENDER_CUTOFF_INDEX) ? "Male" : "Female"),
                                                          raceTable[maxIndex1.index],
                                                          maxIndex2.value, ((maxIndex2.index >= GENDER_CUTOFF_INDEX) ? "Male" : "Female"),
                                                          raceTable[maxIndex2.index],
                                                          maxIndex3.value, ((maxIndex3.index >= GENDER_CUTOFF_INDEX) ? "Male" : "Female"),
                                                          raceTable[maxIndex3.index]);

    printf("\n\n\n");
}
