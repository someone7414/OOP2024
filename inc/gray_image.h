#ifndef _GRAY_IMAGE_H_
#define _GRAY_IMAGE_H_

#include "image.h"

#include <bits/stdc++.h>
using namespace std;

class GrayImage : public Image {
private:
    int** pixels;
    void allocate_pixels(int width, int height);
public:
    GrayImage();
    GrayImage(int width, int height);
    GrayImage(int width, int height, int** pixels);
    GrayImage(const GrayImage& other); // Copy constructor
    GrayImage& operator=(const GrayImage& other); // Assignment operator
    virtual ~GrayImage();
    
    bool LoadImage(const string& filename) override;
    void DumpImage(const string& filename) override;
    void Display_X_Server() override;
    void Display_ASCII() override;
    void Display_CMD() override;
    GrayImage crop(int startX, int startY, int cropWidth, int cropHeight);
    friend class PhotoMosaic;
    friend void applyFilters(GrayImage *image, uint16_t options);
    int** get_pixels() { return pixels; }
};

#endif // GRAY_IMAGE_H
