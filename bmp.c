#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"


unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
    FILE *filePtr; //our file pointer
    BITMAPFILEHEADER bitmapFileHeader; //our bitmap file header
    unsigned char *bitmapImage;  //store image data
    int imageIdx=0;  //image index counter
    unsigned char tempRGB;  //our swap variable
  int i;

    //open filename in read binary mode
    filePtr = fopen(filename,"rb");
    if (filePtr == NULL)
  {
    printf("File read error\n");
        return NULL;
  }

    //read the bitmap file header
    fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER) ,1,filePtr );

    //verify that this is a bmp file by check bitmap id
    if (bitmapFileHeader.bfType !=0x4D42)
    {
    printf("Not bmp file\n");
        fclose(filePtr);
        return NULL;
    }

    //read the bitmap info header
  //printf("Header: %i\n", sizeof(BITMAPFILEHEADER));
  //printf("Short Size: %i\n", sizeof(unsigned short));
  //printf("Int Size: %i\n", sizeof(unsigned int));
  //printf("Long Size: %i\n", sizeof(unsigned long));

    //fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER),1,filePtr);
  //printf("Type: %i\n", bitmapFileHeader.bfType);
  //printf("Size: %i\n", bitmapFileHeader.bfSize);
  //printf("Reserve1: %i\n", bitmapFileHeader.bfReserved1);
  //printf("Reserve2: %i\n", bitmapFileHeader.bfReserved2);


  fseek(filePtr, 10, SEEK_SET);
  fread(&(bitmapFileHeader.bOffBits), sizeof(bitmapFileHeader.bOffBits) ,1, filePtr );
  printf("Bitmap data starts at %i offset\n", bitmapFileHeader.bOffBits);

    fseek(filePtr, 0x22, SEEK_SET);
  fread(&(bitmapInfoHeader->biSizeImage), sizeof(bitmapInfoHeader->biSizeImage) ,1, filePtr );

  // Read Height
  fseek(filePtr, 0x16, SEEK_SET);
  fread(&(bitmapInfoHeader->biHeight), sizeof(bitmapInfoHeader->biHeight) ,1, filePtr );

  // Read Width
  fseek(filePtr, 0x12, SEEK_SET);
  fread(&(bitmapInfoHeader->biWidth), sizeof(bitmapInfoHeader->biWidth) ,1, filePtr );

  printf("WxH: %ix%i\n", bitmapInfoHeader->biWidth, bitmapInfoHeader->biHeight);
    //move file point to the begging of bitmap data
    fseek(filePtr, bitmapFileHeader.bOffBits, SEEK_SET);



  printf("Attempting to allocate %i bytes of memory\n", bitmapInfoHeader->biSizeImage);
    //allocate enough memory for the bitmap image data
    bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

    //verify memory allocation
    if (bitmapImage == NULL)
    {
    printf("Memory allocation error\n");
        free(bitmapImage);
        fclose(filePtr);
        return NULL;
    }

    //read in the bitmap image data
    fread(bitmapImage,4,bitmapInfoHeader->biSizeImage,filePtr);



    //make sure bitmap image data was read
    if (bitmapImage == NULL)
    {
    printf("Image data not read\n");
        fclose(filePtr);
        return NULL;
    }

    //swap the r and b values to get RGB (bitmap is BGR)
    for (imageIdx = 0;imageIdx < bitmapInfoHeader->biSizeImage;imageIdx+=3)
    {
        tempRGB = bitmapImage[imageIdx];
        bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
        bitmapImage[imageIdx + 2] = tempRGB;
    }

    //close file and return bitmap iamge data
    fclose(filePtr);

  printf("Printing Image\n");
  for (i=0;i<bitmapInfoHeader->biHeight * bitmapInfoHeader->biWidth;i++)
  {
    printf("%i,", bitmapImage[i]);
  }
  printf("\n---------------\n");

    return bitmapImage;
}
