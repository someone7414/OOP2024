#ifndef _PHOTO_MOSAIC_H_
#define _PHOTO_MOSAIC_H_

#include "rgb_image.h"
#include "gray_image.h"

#include <bits/stdc++.h>
using namespace std;

struct RGB {
    int r;
    int g;
    int b;
    RGB() : r(0), g(0), b(0) {}
    RGB(int red, int green, int blue) : r(red), g(green), b(blue) {}
};

class PhotoMosaic : public RGBImage {
private:
    int*** pixels;

    RGB* getAverageRGB(RGBImage& image);
    int* getAverageGray(GrayImage& image);

    vector<RGBImage*> splitImage(RGBImage& image, int& width, int& height);
    vector<GrayImage*> splitImage(GrayImage& image, int& width, int& height);

    int getBestMatchIndex(const RGB& targetAvg, const vector<RGB*>& avgs);
    int getBestMatchIndex(const int& targetAvg, const vector<int*>& avgs);

    RGBImage createImageGrid(vector<RGBImage*>& images, int& rows, int& cols);
    RGBImage createImageGrid(vector<GrayImage*>& images, int& rows, int& cols);

    vector<RGBImage> getRGBImages(const string& directory);
    vector<GrayImage> getGrayImages(const string& directory);

public:
    PhotoMosaic();
    PhotoMosaic(int width, int height, int*** pixels);
    virtual ~PhotoMosaic();
    void createPhotomosaic(const string& targetImagePath, const string& inputFolderPath, bool rgb);
};

#endif // _PHOTO_MOSAIC_H_
