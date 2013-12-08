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
    char* people[8] = {"briggs.bmp", "bryant.bmp", "allen.bmp", "cabric.bmp", "bryant2.bmp", "abidi.bmp", "feminine.bmp", "hayden.bmp"};
    int i;

    testMatrix();
    testFace();

    for (i = 0; i < 8; i++) {
      genderDetection(people[i]);
    }
}
