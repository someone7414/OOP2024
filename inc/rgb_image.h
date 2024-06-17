#ifndef _RGB_IMAGE_H_
#define _RGB_IMAGE_H_

#include "image.h"

#include <bits/stdc++.h>
using namespace std;

class RGBImage : public Image {
protected:
    int*** pixels;
    void allocate_pixels(int width, int height);
public:
    RGBImage();
    RGBImage(int width, int height);
    RGBImage(int width, int height, int*** pixels);
    RGBImage(const RGBImage &other);
    RGBImage& operator=(const RGBImage &other);
    virtual ~RGBImage();
    
    bool LoadImage(const string& filename) override;
    void DumpImage(const string& filename) override;
    void Display_X_Server() override;
    void Display_ASCII() override;
    void Display_CMD() override;
    RGBImage crop(int startX, int startY, int crop_width, int crop_height);
    friend class PhotoMosaic;
    friend void applyFilters(RGBImage *image, uint16_t options);
    int*** get_pixels() { return pixels; }
};

#endif // RGB_IMAGE_H
