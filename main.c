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
    testMatrix();
    testFace();

    BITMAPINFOHEADER bmpInfoHeader;
    loadBitmapFileGrayscale("abidi.bmp", &bmpInfoHeader);
}
