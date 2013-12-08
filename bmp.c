#include <stdio.h>
#include <stdlib.h>
#include "ee113d.h"
#include "bmp.h"

// RGB weights for grayscale conversion
#define GRAYSCALE_R 0.2989
#define GRAYSCALE_G 0.5870
#define GRAYSCALE_B 0.1140


// use external RAM for DSK



double* loadBitmapFileGrayscale(char *filename, BITMAPINFOHEADER *bitmapInfoHeader) {
    FILE *filePtr; // our file pointer
    BITMAPFILEHEADER bitmapFileHeader; //our bitmap file header

    unsigned char* bitmapImage;
    double*        grayBitmapImage;


    int i,invertedI, h,w, rowOffset, paddingBytes;

    // open filename in read binary mode
    filePtr = fopen(filename, "rb");
    if (filePtr == NULL) {
        printf("File read error\n");
        return NULL;
    }

    //read the bitmap file header
    fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);

    // verify that this is a bmp file by check bitmap id
    if (bitmapFileHeader.bfType !=0x4D42) {
        printf("Not bmp file\n");
        fclose(filePtr);
        return NULL;
    }

    // Read headers
    fseek(filePtr, 10, SEEK_SET);
    fread(&(bitmapFileHeader.bOffBits), sizeof(bitmapFileHeader.bOffBits), 1, filePtr);
    printf("Bitmap data starts at %i offset\n", bitmapFileHeader.bOffBits);

    fseek(filePtr, 0x22, SEEK_SET);
    fread(&(bitmapInfoHeader->biSizeImage), sizeof(bitmapInfoHeader->biSizeImage), 1, filePtr);

    // Read Height
    fseek(filePtr, 0x16, SEEK_SET);
    fread(&(bitmapInfoHeader->biHeight), sizeof(bitmapInfoHeader->biHeight), 1, filePtr);

    // Read Width
    fseek(filePtr, 0x12, SEEK_SET);
    fread(&(bitmapInfoHeader->biWidth), sizeof(bitmapInfoHeader->biWidth), 1, filePtr);

    printf("WxH: %ix%i\n", bitmapInfoHeader->biWidth, bitmapInfoHeader->biHeight);

    //move file point to the begging of bitmap data
    fseek(filePtr, bitmapFileHeader.bOffBits, SEEK_SET);


    // allocate memory for bitmap image data
    bitmapImage = (unsigned char*)malloc(sizeof(unsigned char) * bitmapInfoHeader->biSizeImage);

    if (bitmapImage == NULL) {
        printf("Memory allocation failure\n");
        free(bitmapImage);
        fclose(filePtr);
        return NULL;
    }


    // read in the bitmap image data
    fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);

    // make sure bitmap image data was read
    if (bitmapImage == NULL) {
        printf("Image data not read\n");
        fclose(filePtr);
        return NULL;
    }

    //close file and return bitmap image data
    fclose(filePtr);


    // unreverse row data, grayscale, and return array data as doubles
    paddingBytes = (4 - (bitmapInfoHeader->biWidth*3 % 4)) % 4;
    rowOffset = 0;


    grayBitmapImage = (double*)malloc(sizeof(double) * bitmapInfoHeader->biHeight * bitmapInfoHeader->biWidth);


    for (h = 0; h < bitmapInfoHeader->biHeight; h++) {
      for (w = 0; w < bitmapInfoHeader->biWidth; w++) {
        i = bitmapInfoHeader->biWidth * h + w;
        invertedI = bitmapInfoHeader->biWidth*(bitmapInfoHeader->biHeight-1-h) + w;

        // gbr -> rgb, grayscale, and normalize
        grayBitmapImage[invertedI] = (GRAYSCALE_R * (double)(bitmapImage[i*3 + rowOffset + 2]) +
                                      GRAYSCALE_G * (double)(bitmapImage[i*3 + rowOffset + 1]) +
                                      GRAYSCALE_B * (double)(bitmapImage[i*3 + rowOffset + 0])) / 255.0;
        //printf("%f,", grayBitmapImage[invertedI]);
      }
      //printf("\n");
      rowOffset += paddingBytes;
    }


    free(bitmapImage);


    return grayBitmapImage;
}

double* loadGrayBitmapFileGrayscale(char *filename, BITMAPINFOHEADER *bitmapInfoHeader) {
    FILE *filePtr; // our file pointer
    BITMAPFILEHEADER bitmapFileHeader; //our bitmap file header

    unsigned char* bitmapImage;
    double*        grayBitmapImage;


    int i,invertedI, h,w, rowOffset, paddingBytes;

    // open filename in read binary mode
    filePtr = fopen(filename, "rb");
    if (filePtr == NULL) {
        printf("File read error\n");
        return NULL;
    }

    //read the bitmap file header
    fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);

    // verify that this is a bmp file by check bitmap id
    if (bitmapFileHeader.bfType !=0x4D42) {
        printf("Not bmp file\n");
        fclose(filePtr);
        return NULL;
    }

    // Read headers
    fseek(filePtr, 10, SEEK_SET);
    fread(&(bitmapFileHeader.bOffBits), sizeof(bitmapFileHeader.bOffBits), 1, filePtr);
    printf("Bitmap data starts at %i offset\n", bitmapFileHeader.bOffBits);

    fseek(filePtr, 0x22, SEEK_SET);
    fread(&(bitmapInfoHeader->biSizeImage), sizeof(bitmapInfoHeader->biSizeImage), 1, filePtr);

    // Read Height
    fseek(filePtr, 0x16, SEEK_SET);
    fread(&(bitmapInfoHeader->biHeight), sizeof(bitmapInfoHeader->biHeight), 1, filePtr);

    // Read Width
    fseek(filePtr, 0x12, SEEK_SET);
    fread(&(bitmapInfoHeader->biWidth), sizeof(bitmapInfoHeader->biWidth), 1, filePtr);

    printf("WxH: %ix%i\n", bitmapInfoHeader->biWidth, bitmapInfoHeader->biHeight);

    //move file point to the begging of bitmap data
    fseek(filePtr, bitmapFileHeader.bOffBits, SEEK_SET);


    // allocate memory for bitmap image data
    bitmapImage = (unsigned char*)malloc(sizeof(unsigned char) * bitmapInfoHeader->biSizeImage);

    if (bitmapImage == NULL) {
        printf("Memory allocation failure\n");
        free(bitmapImage);
        fclose(filePtr);
        return NULL;
    }


    // read in the bitmap image data
    fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);

    // make sure bitmap image data was read
    if (bitmapImage == NULL) {
        printf("Image data not read\n");
        fclose(filePtr);
        return NULL;
    }

    //close file and return bitmap image data
    fclose(filePtr);


    // unreverse row data, grayscale, and return array data as doubles
    paddingBytes = (4 - (bitmapInfoHeader->biWidth % 4)) % 4;
    rowOffset = 0;


    grayBitmapImage = (double*)malloc(sizeof(double) * bitmapInfoHeader->biHeight * bitmapInfoHeader->biWidth);


    for (h = 0; h < bitmapInfoHeader->biHeight; h++) {
      for (w = 0; w < bitmapInfoHeader->biWidth; w++) {
        i = bitmapInfoHeader->biWidth * h + w;
        invertedI = bitmapInfoHeader->biWidth*(bitmapInfoHeader->biHeight-1-h) + w;

        // gbr -> rgb, grayscale, and normalize
        grayBitmapImage[invertedI] = ((double)(bitmapImage[i + rowOffset])) / 255.0;
      }
      rowOffset += paddingBytes;
    }


    free(bitmapImage);


    return grayBitmapImage;
}


