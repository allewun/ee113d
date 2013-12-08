//
// main.c
// Facial gender detection
//
//
// EE 113D - Fall 2013
//  * Allen Wu
//  * Bryant Khau
//

#include "test.h"
#include "bmp.h"

void main() {
    BITMAPINFOHEADER bmpInfoHeader;
    testMatrix();
    testFace();


    loadBitmapFileGrayscale("abidi.bmp", &bmpInfoHeader);
}
