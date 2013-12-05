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

double similarityScore(double n, Matrix a, Matrix b) {
    // nth column of matrix A
    Matrix left = column(a, n);
    Matrix right = b;

    return 1 / vectorNorm(subtract(left, right));
}

double times2(double a) {
    return a*2;
}