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
#include "face.h"

void main() {
    char* people[4] = {"briggs.bmp", "bryant.bmp", "allen.bmp", "cabric.bmp"};
    int i;

    testMatrix();
    testFace();

    for (i = 0; i < 4; i++) {
      genderDetection(people[i]);
    }
}
