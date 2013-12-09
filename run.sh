#!/bin/sh

# 1. put input images in input/
#      size: 112x150
#      type: .bmp
# 2. Update main.c
# 3. Run this

gcc -o detect *.c -Wall && ./detect --heap=0xa00000
