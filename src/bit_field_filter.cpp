#include "bit_field_filter.h"

#include <bits/stdc++.h>
using namespace std;

void applyBoxFilter(int width, int height, int **pixels) {
    cout << "Applying Box Filter" << endl;
    int kernelSize = 3;
    cout << "Enter a kernel size (odd number between 3 and 15): ";
    cin >> kernelSize;
    while (kernelSize < 3 || kernelSize > 15 || kernelSize % 2 == 0) {
        cout << "Invalid input. Please enter an odd value between 3 and 15: ";
        cin >> kernelSize;
    }

    int kernelRadius = kernelSize / 2;
    int **tempImage = new int*[height];
    for (int i = 0; i < height; ++i) {
        tempImage[i] = new int[width];
    }

    for (int i = kernelRadius; i < height - kernelRadius; ++i) {
        for (int j = kernelRadius; j < width - kernelRadius; ++j) {
            int sum = 0;
            for (int ki = -kernelRadius; ki <= kernelRadius; ++ki) {
                for (int kj = -kernelRadius; kj <= kernelRadius; ++kj) {
                    sum += pixels[i + ki][j + kj];
                }
            }
            tempImage[i][j] = sum / (kernelSize * kernelSize);
        }
    }

    for (int i = kernelRadius; i < height - kernelRadius; ++i) {
        for (int j = kernelRadius; j < width - kernelRadius; ++j) {
            pixels[i][j] = tempImage[i][j];
        }
    }

    for (int i = 0; i < height; ++i) {
        delete[] tempImage[i];
    }
    delete[] tempImage;
}

void applySobelGradient(int width, int height, int **pixels) {
    cout << "Applying Sobel Gradient Filter" << endl;
    int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int Gy[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    int **tempImage = new int*[height];
    for (int i = 0; i < height; ++i) {
        tempImage[i] = new int[width];
    }

    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < width - 1; ++j) {
            int sumX = 0;
            int sumY = 0;
            for (int ki = -1; ki <= 1; ++ki) {
                for (int kj = -1; kj <= 1; ++kj) {
                    sumX += pixels[i + ki][j + kj] * Gx[ki + 1][kj + 1];
                    sumY += pixels[i + ki][j + kj] * Gy[ki + 1][kj + 1];
                }
            }
            tempImage[i][j] = sqrt(sumX * sumX + sumY * sumY);
        }
    }

    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < width - 1; ++j) {
            pixels[i][j] = tempImage[i][j];
        }
    }

    for (int i = 0; i < height; ++i) {
        delete[] tempImage[i];
    }
    delete[] tempImage;
}

void applyContrastStretch(int width, int height, int **pixels) {
    cout << "Applying Contrast Stretch Filter" << endl;
    int minVal = 255, maxVal = 0;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (pixels[i][j] < minVal) minVal = pixels[i][j];
            if (pixels[i][j] > maxVal) maxVal = pixels[i][j];
        }
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            pixels[i][j] = 255 * (pixels[i][j] - minVal) / (maxVal - minVal);
        }
    }
}

void applyMosaicFilter(int width, int height, int **pixels) {
    cout << "Applying Mosaic Filter" << endl;
    int blockSize = 10;
    cout << "Enter a blockSize (between 3 and 10): ";
    cin >> blockSize;
    while (blockSize < 3 || blockSize > 10) {
        cout << "Invalid input. Please enter a value between 3 and 10: ";
        cin >> blockSize;
    }

    for (int i = 0; i < height; i += blockSize) {
        for (int j = 0; j < width; j += blockSize) {
            int sum = 0;
            int count = 0;
            for (int ki = 0; ki < blockSize; ++ki) {
                for (int kj = 0; kj < blockSize; ++kj) {
                    if (i + ki < height && j + kj < width) {
                        sum += pixels[i + ki][j + kj];
                        count++;
                    }
                }
            }
            int avg = sum / count;
            for (int ki = 0; ki < blockSize; ++ki) {
                for (int kj = 0; kj < blockSize; ++kj) {
                    if (i + ki < height && j + kj < width) {
                        pixels[i + ki][j + kj] = avg;
                    }
                }
            }
        }
    }
}

void applyGaussianBlur(int width, int height, int **pixels) {
    cout << "Applying Gaussian Blur" << endl;
    int kernelSize = 3;
    const float sigma = 1.0f;
    float kernel[kernelSize][kernelSize];
    float sum = 0.0f;

    for (int x = -kernelSize/2; x <= kernelSize/2; ++x) {
        for (int y = -kernelSize/2; y <= kernelSize/2; ++y) {
            float exponent = -((x * x + y * y) / (2 * sigma * sigma));
            kernel[x + kernelSize/2][y + kernelSize/2] = exp(exponent) / (2 * M_PI * sigma * sigma);
            sum += kernel[x + kernelSize/2][y + kernelSize/2];
        }
    }

    for (int i = 0; i < kernelSize; ++i) {
        for (int j = 0; j < kernelSize; ++j) {
            kernel[i][j] /= sum;
        }
    }

    int **tempImage = new int*[height];
    for (int i = 0; i < height; ++i) {
        tempImage[i] = new int[width];
    }

    for (int i = kernelSize/2; i < height - kernelSize/2; ++i) {
        for (int j = kernelSize/2; j < width - kernelSize/2; ++j) {
            float sum = 0.0f;
            for (int ki = -kernelSize/2; ki <= kernelSize/2; ++ki) {
                for (int kj = -kernelSize/2; kj <= kernelSize/2; ++kj) {
                    sum += pixels[i + ki][j + kj] * kernel[ki + kernelSize/2][kj + kernelSize/2];
                }
            }
            tempImage[i][j] = static_cast<int>(sum);
        }
    }

    for (int i = kernelSize/2; i < height - kernelSize/2; ++i) {
        for (int j = kernelSize/2; j < width - kernelSize/2; ++j) {
            pixels[i][j] = tempImage[i][j];
        }
    }

    for (int i = 0; i < height; ++i) {
        delete[] tempImage[i];
    }
    delete[] tempImage;
}

void applyMedianFilter(int width, int height, int **pixels) {
    cout << "Applying Median Filter" << endl;
    int kernelSize = 3;
    int **tempImage = new int*[height];
    for (int i = 0; i < height; ++i) {
        tempImage[i] = new int[width];
    }

    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < width - 1; ++j) {
            int window[kernelSize * kernelSize];
            int count = 0;
            for (int ki = -1; ki <= 1; ++ki) {
                for (int kj = -1; kj <= 1; ++kj) {
                    window[count++] = pixels[i + ki][j + kj];
                }
            }
            sort(window, window + kernelSize * kernelSize);
            tempImage[i][j] = window[kernelSize * kernelSize / 2];
        }
    }

    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < width - 1; ++j) {
            pixels[i][j] = tempImage[i][j];
        }
    }

    for (int i = 0; i < height; ++i) {
        delete[] tempImage[i];
    }
    delete[] tempImage;
}

void applySharpenFilter(int width, int height, int **pixels) {
    cout << "Applying Sharpen Filter" << endl;
    int kernel[3][3] = {
        { 0, -1,  0},
        {-1,  5, -1},
        { 0, -1,  0}
    };

    int **tempImage = new int*[height];
    for (int i = 0; i < height; ++i) {
        tempImage[i] = new int[width];
    }

    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < width - 1; ++j) {
            int sum = 0;
            for (int ki = -1; ki <= 1; ++ki) {
                for (int kj = -1; kj <= 1; ++kj) {
                    sum += pixels[i + ki][j + kj] * kernel[ki + 1][kj + 1];
                }
            }
            tempImage[i][j] = max(0, min(255, sum));
        }
    }

    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < width - 1; ++j) {
            pixels[i][j] = tempImage[i][j];
        }
    }

    for (int i = 0; i < height; ++i) {
        delete[] tempImage[i];
    }
    delete[] tempImage;
}

void applyLinearMotionBlur(int width, int height, int **pixels) {
    cout << "Applying Linear Motion Blur Filter" << endl;
    int kernelSize = 5;
    double angle = 0.0; // in degrees
    cout << "Enter a kernel size (odd number between 10 and 50): ";
    cin >> kernelSize;
    while (kernelSize < 5 || kernelSize > 50 || kernelSize % 2 == 0) {
        cout << "Invalid input. Please enter an odd value between 10 and 50: ";
        cin >> kernelSize;
    }
    cout << "Enter the angle of motion blur in degrees: ";
    cin >> angle;

    int kernelRadius = kernelSize / 2;
    double radian = angle * M_PI / 180.0;
    int **tempImage = new int*[height];
    for (int i = 0; i < height; ++i) {
        tempImage[i] = new int[width];
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int sum = 0;
            int count = 0;
            for (int k = -kernelRadius; k <= kernelRadius; ++k) {
                int x = j + k * cos(radian);
                int y = i + k * sin(radian);
                if (x >= 0 && x < width && y >= 0 && y < height) {
                    sum += pixels[y][x];
                    ++count;
                }
            }
            tempImage[i][j] = sum / count;
        }
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            pixels[i][j] = tempImage[i][j];
        }
    }

    for (int i = 0; i < height; ++i) {
        delete[] tempImage[i];
    }
    delete[] tempImage;
}

void applyInvertFilter(int width, int height, int ***pixels) {
    cout << "Applying Invert Filter" << endl;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            pixels[y][x][0] = 255 - pixels[y][x][0];
            pixels[y][x][1] = 255 - pixels[y][x][1];
            pixels[y][x][2] = 255 - pixels[y][x][2];
        }
    }
}

void applySepiaFilter(int width, int height, int ***pixels) {
    cout << "Applying Sepia Filter" << endl;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int tr = (0.393 * pixels[y][x][0]) + (0.769 * pixels[y][x][1]) + (0.189 * pixels[y][x][2]);
            int tg = (0.349 * pixels[y][x][0]) + (0.686 * pixels[y][x][1]) + (0.168 * pixels[y][x][2]);
            int tb = (0.272 * pixels[y][x][0]) + (0.534 * pixels[y][x][1]) + (0.131 * pixels[y][x][2]);
            pixels[y][x][0] = min(tr, 255);
            pixels[y][x][1] = min(tg, 255);
            pixels[y][x][2] = min(tb, 255);
        }
    }
}

void applyContrastFilter(int width, int height, int ***pixels) {
    cout << "Applying Contrast Filter" << endl;
    float contrast = 100;
    float factor = (259 * (contrast + 255)) / (255 * (259 - contrast));
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            pixels[y][x][0] = min(max(factor * (pixels[y][x][0] - 128) + 128, 0.0f), 255.0f);
            pixels[y][x][1] = min(max(factor * (pixels[y][x][1] - 128) + 128, 0.0f), 255.0f);
            pixels[y][x][2] = min(max(factor * (pixels[y][x][2] - 128) + 128, 0.0f), 255.0f);
        }
    }
}

void applyEdgeDetectionFilter(int width, int height, int ***pixels) {
    cout << "Applying Edge Detection Filter" << endl;
    int ***tempPixels = new int**[height];
    for (int i = 0; i < height; ++i) {
        tempPixels[i] = new int*[width];
        for (int j = 0; j < width; ++j) {
            tempPixels[i][j] = new int[3];
            tempPixels[i][j][0] = pixels[i][j][0];
            tempPixels[i][j][1] = pixels[i][j][1];
            tempPixels[i][j][2] = pixels[i][j][2];
        }
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int gx = 0, gy = 0;
            if (y > 0 && y < height - 1 && x > 0 && x < width - 1) {
                gx = (
                    -1 * tempPixels[y - 1][x - 1][0] + 0 * tempPixels[y - 1][x][0] + 1 * tempPixels[y - 1][x + 1][0] +
                    -2 * tempPixels[y][x - 1][0] + 0 * tempPixels[y][x][0] + 2 * tempPixels[y][x + 1][0] +
                    -1 * tempPixels[y + 1][x - 1][0] + 0 * tempPixels[y + 1][x][0] + 1 * tempPixels[y + 1][x + 1][0]
                );
                gy = (
                    -1 * tempPixels[y - 1][x - 1][0] + -2 * tempPixels[y - 1][x][0] + -1 * tempPixels[y - 1][x + 1][0] +
                     0 * tempPixels[y][x - 1][0] +  0 * tempPixels[y][x][0] +  0 * tempPixels[y][x + 1][0] +
                     1 * tempPixels[y + 1][x - 1][0] +  2 * tempPixels[y + 1][x][0] +  1 * tempPixels[y + 1][x + 1][0]
                );
            }
            int mag = sqrt(gx * gx + gy * gy);
            mag = min(mag, 255);
            pixels[y][x][0] = pixels[y][x][1] = pixels[y][x][2] = mag;
        }
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            delete[] tempPixels[i][j];
        }
        delete[] tempPixels[i];
    }
    delete[] tempPixels;
}

float cubicInterpolate(float p0, float p1, float p2, float p3, float x) {
    return p1 + 0.5f * x * (p2 - p0 + x * (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3 + x * (3.0f * (p1 - p2) + p3 - p0)));
}

float bicubicInterpolate(float p[4][4], float x, float y) {
    float arr[4];
    arr[0] = cubicInterpolate(p[0][0], p[0][1], p[0][2], p[0][3], x);
    arr[1] = cubicInterpolate(p[1][0], p[1][1], p[1][2], p[1][3], x);
    arr[2] = cubicInterpolate(p[2][0], p[2][1], p[2][2], p[2][3], x);
    arr[3] = cubicInterpolate(p[3][0], p[3][1], p[3][2], p[3][3], x);
    return cubicInterpolate(arr[0], arr[1], arr[2], arr[3], y);
}

void upscaleImage(int oldWidth, int oldHeight, int **oldPixels, int newWidth, int newHeight, int **newPixels) {
    float xRatio = static_cast<float>(oldWidth - 1) / (newWidth - 1);
    float yRatio = static_cast<float>(oldHeight - 1) / (newHeight - 1);

    for (int i = 0; i < newHeight; ++i) {
        for (int j = 0; j < newWidth; ++j) {
            float x = xRatio * j;
            float y = yRatio * i;
            int xInt = static_cast<int>(x);
            int yInt = static_cast<int>(y);
            float xDiff = x - xInt;
            float yDiff = y - yInt;

            float patch[4][4];
            for (int m = -1; m <= 2; ++m) {
                for (int n = -1; n <= 2; ++n) {
                    int xi = min(max(xInt + m, 0), oldWidth - 1);
                    int yi = min(max(yInt + n, 0), oldHeight - 1);
                    patch[m + 1][n + 1] = oldPixels[yi][xi];
                }
            }

            newPixels[i][j] = static_cast<int>(bicubicInterpolate(patch, xDiff, yDiff));
        }
    }

    cout << "Upscaling Image Using Bicubic Interpolation" << endl;
}

void applyFilters(GrayImage *image, uint16_t options) {
    int width = image->width;
    int height = image->height;
    int** pixels = image->pixels;
    if (options & BOX_FILTER) applyBoxFilter(width, height, pixels);
    if (options & SOBEL_GRADIENT) applySobelGradient(width, height, pixels);
    if (options & CONTRAST_STRETCH) applyContrastStretch(width, height, pixels);
    if (options & MOSAIC_FILTER) applyMosaicFilter(width, height, pixels);
    if (options & GAUSSIAN_BLUR) applyGaussianBlur(width, height, pixels);
    if (options & MEDIAN_FILTER) applyMedianFilter(width, height, pixels);
    if (options & SHARPEN_FILTER) applySharpenFilter(width, height, pixels);
    if (options & LINEAR_MOTION_BLUR) applyLinearMotionBlur(width, height, pixels);
}

void applyFilters(RGBImage *image, uint16_t options) {
    int width = image->width;
    int height = image->height;
    int*** pixels = image->pixels;
    if (options & INVERT_FILTER) applyInvertFilter(width, height, pixels);
    if (options & SEPIA_FILTER) applySepiaFilter(width, height, pixels);
    if (options & CONTRAST_FILTER) applyContrastFilter(width, height, pixels);
    if (options & EDGE_DETECTION) applyEdgeDetectionFilter(width, height, pixels);
}