#ifndef __IMAGE_h
#define __IMAGE_h

#include <cstdio>
#include <cstdint>
#include <cmath>

void generate_bmp_img( \
    uint8_t* image, \
    int height, \
    int width, \
    const char* filename
);

#endif

/*
 *
 * - CONTOH -
 * 
 * int width = 100, height = 100;
 * uint8_t image[height][width][3];
 * 
 * image[0][0][2] = red;
 * image[0][0][1] = green;
 * image[0][0][0] = blue;
 * 
 * generate_bmp_img((uint8_t*)image, height, width, "result.bmp");
 * 
 */