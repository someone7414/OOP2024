#ifndef _FILTERS_H_
#define _FILTERS_H_

#include <bits/stdc++.h>
using namespace std;

#include "gray_image.h"
#include "rgb_image.h"

//GRAY
#define BOX_FILTER 0b0000000000000001
#define SOBEL_GRADIENT 0b0000000000000010
#define CONTRAST_STRETCH 0b0000000000000100
#define MOSAIC_FILTER 0b0000000000001000
#define GAUSSIAN_BLUR 0b0000000000010000
#define MEDIAN_FILTER 0b0000000000100000
#define SHARPEN_FILTER 0b0000000001000000
#define LINEAR_MOTION_BLUR 0b0000000010000000

//RGB
#define INVERT_FILTER 0b0000000100000000
#define SEPIA_FILTER 0b0000001000000000
#define CONTRAST_FILTER 0b0000010000000000
#define EDGE_DETECTION 0b0000100000000000

//Gray
void applyBoxFilter(int width, int height, int **pixels);
void applySobelGradient(int width, int height, int **pixels);
void applyContrastStretch(int width, int height, int **pixels);
void applyMosaicFilter(int width, int height, int **pixels);
void applyGaussianBlur(int width, int height, int **pixels);
void applyMedianFilter(int width, int height, int **pixels);
void applySharpenFilter(int width, int height, int **pixels);
//RGB
void applyInvertFilter(int width, int height, int ***pixels);
void applySepiaFilter(int width, int height, int ***pixels);
void applyContrastFilter(int width, int height, int ***pixels);
void applyEdgeDetectionFilter(int width, int height, int ***pixels);

void upscaleImage(int oldWidth, int oldHeight, int **oldPixels, int newWidth, int newHeight, int **newPixels);

//void applyFilters(int width, int height, int **pixels, uint16_t options);
//void applyFilters(int width, int height, int ***pixels, uint16_t options);

#endif // _FILTERS_H_
