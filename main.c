//
// main.c
// Facial gender detection
//
//
// EE 113D - Fall 2013
//  * Allen Wu
//  * Bryant Khau
//

#include "bmp.h"
#include "face.h"

void main() {
    char* people[] = {"briggs.bmp",
                      "bryant.bmp",
                      "allen.bmp",
                      "cabric.bmp",
                      "bryant2.bmp",
                      "abidi.bmp",
                      "feminine.bmp",
                      "hayden.bmp"};
    int i;

    for (i = 0; i < sizeof(people)/sizeof(people[0]); i++) {
      genderDetection(people[i]);
    }
}
