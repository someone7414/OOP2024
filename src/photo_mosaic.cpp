#include "photo_mosaic.h"
#include <bits/stdc++.h>
using namespace std;

PhotoMosaic::PhotoMosaic() : RGBImage(0, 0), pixels(nullptr) {}

PhotoMosaic::PhotoMosaic(int w, int h, int ***pixels) :  RGBImage(w, h), pixels(pixels) {}

PhotoMosaic::~PhotoMosaic() {
    if (pixels) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                delete[] pixels[i][j];
            }
            delete[] pixels[i];
        }
        delete[] pixels;
    }
}

RGB* PhotoMosaic::getAverageRGB(RGBImage& image) {
    long sumR = 0, sumG = 0, sumB = 0;
    int w = image.get_width();
    int h = image.get_height();
    int numPixels = w * h;

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            sumR += image.pixels[y][x][0];    // R
            sumG += image.pixels[y][x][1];    // G
            sumB += image.pixels[y][x][2];    // B
        }
    }

    return new RGB(sumR / numPixels, sumG / numPixels, sumB / numPixels);
}

int* PhotoMosaic::getAverageGray(GrayImage& image) {
    long sumGray = 0;
    int w = image.get_width();
    int h = image.get_height();
    int numPixels = w * h;

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            sumGray += image.pixels[y][x];
        }
    }

    return new int(sumGray / numPixels);
}

vector<RGBImage*> PhotoMosaic::splitImage(RGBImage& image, int& w, int& h) {
    int imgHeight = image.get_height();
    int imgWidth = image.get_width();
    int rows = imgHeight / h;
    int cols = imgWidth / w;

    cout << "Image dimensions: " << imgWidth << "x" << imgHeight << endl;
    cout << "Grid size: " << rows << " rows x " << cols << " cols" << endl;

    vector<RGBImage*> images;

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int startX = col * w;
            int startY = row * h;
            RGBImage* cropped = new RGBImage(image.crop(startX, startY, w, h));
            images.push_back(cropped);
        }
    }

    return images;
}

vector<GrayImage*> PhotoMosaic::splitImage(GrayImage& image, int& w, int& h) {
    int imgHeight = image.get_height();
    int imgWidth = image.get_width();
    int rows = imgHeight / h;
    int cols = imgWidth / w;

    cout << "Image dimensions: " << imgWidth << "x" << imgHeight << endl;
    cout << "Grid size: " << rows << " rows x " << cols << " cols" << endl;

    vector<GrayImage*> images;

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int startX = col * w;
            int startY = row * h;
            GrayImage* cropped = new GrayImage(image.crop(startX, startY, w, h));
            images.push_back(cropped);
        }
    }

    return images;
}

int PhotoMosaic::getBestMatchIndex(const RGB& targetAvg, const vector<RGB*>& avgs) {
    int minIndex = 0;
    double minDist = numeric_limits<double>::max();

    for (size_t i = 0; i < avgs.size(); ++i) {
        double dist = pow(avgs[i]->r - targetAvg.r, 2) + pow(avgs[i]->g - targetAvg.g, 2) + pow(avgs[i]->b - targetAvg.b, 2);
        if (dist < minDist) {
            minDist = dist;
            minIndex = i;
        }
    }

    return minIndex;
}

int PhotoMosaic::getBestMatchIndex(const int& targetAvg, const vector<int*>& avgs) {
    int minIndex = 0;
    int minDist = numeric_limits<int>::max();

    for (size_t i = 0; i < avgs.size(); ++i) {
        int dist = abs(*avgs[i] - targetAvg);
        if (dist < minDist) {
            minDist = dist;
            minIndex = i;
        }
    }

    return minIndex;
}

RGBImage PhotoMosaic::createImageGrid(vector<RGBImage*>& images, int& rows, int& cols) {
    int w = images[0]->get_width();
    int h = images[0]->get_height();
    RGBImage grid(cols * w, rows * h);

    cout << "Creating mosaic grid with dimensions: " << (cols * w) << "x" << (rows * h) << endl;

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            RGBImage* image = images[row * cols + col];
            int startX = col * w;
            int startY = row * h;
            int imgWidth = image->get_width();
            int imgHeight = image->get_height();
            int*** imgPixels = image->pixels;
            for (int y = 0; y < imgHeight; ++y) {
                for (int x = 0; x < imgWidth; ++x) {
                    if (startY + y < rows * h && startX + x < cols * w) {
                        grid.pixels[startY + y][startX + x][0] = imgPixels[y][x][0]; // R
                        grid.pixels[startY + y][startX + x][1] = imgPixels[y][x][1]; // G
                        grid.pixels[startY + y][startX + x][2] = imgPixels[y][x][2]; // B
                    }
                }
            }
        }
    }

    return grid;
}

RGBImage PhotoMosaic::createImageGrid(vector<GrayImage*>& images, int& rows, int& cols) {
    int w = images[0]->get_width();
    int h = images[0]->get_height();
    GrayImage grid(cols * w, rows * h);

    cout << "Creating mosaic grid with dimensions: " << (cols * w) << "x" << (rows * h) << endl;
    RGBImage out(cols * w, rows * h);
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            GrayImage* image = images[row * cols + col];
            int startX = col * w;
            int startY = row * h;
            int imgWidth = image->get_width();
            int imgHeight = image->get_height();
            int** imgPixels = image->pixels;
            for (int y = 0; y < imgHeight; ++y) {
                for (int x = 0; x < imgWidth; ++x) {
                    if (startY + y < rows * h && startX + x < cols * w) {
                        grid.pixels[startY + y][startX + x] = imgPixels[y][x];
                        out.pixels[startY + y][startX + x][0] = imgPixels[y][x];
                        out.pixels[startY + y][startX + x][1] = imgPixels[y][x];
                        out.pixels[startY + y][startX + x][2] = imgPixels[y][x];
                    }
                }
            }
        }
    }
    return out;
}

vector<RGBImage> PhotoMosaic::getRGBImages(const string& directory) {
    vector<string> filenames;
    data_loader.List_Directory(directory, filenames);
    vector<RGBImage> images(filenames.size());
    for (size_t i = 0; i < filenames.size(); ++i) {
        images[i].LoadImage(filenames[i]);
    }
    return images;
}

vector<GrayImage> PhotoMosaic::getGrayImages(const string& directory) {
    vector<string> filenames;
    data_loader.List_Directory(directory, filenames);
    vector<GrayImage> images(filenames.size());
    for (size_t i = 0; i < filenames.size(); ++i) {
        images[i].LoadImage(filenames[i]);
    }
    return images;
}

void PhotoMosaic::createPhotomosaic(const string& targetImagePath, const string& inputFolderPath, bool rgb) {
    if (rgb) {
        RGBImage targetImage;
        targetImage.LoadImage(targetImagePath);
        vector<RGBImage> inputImages = getRGBImages(inputFolderPath);
        int inputWidth = inputImages[0].get_width();
        int inputHeight = inputImages[0].get_height();
        cout << "Input image dimensions: " << inputWidth << "x" << inputHeight << endl;

        cout << "Splitting input image..." << endl;  
        vector<RGBImage*> targetImages = splitImage(targetImage, inputWidth, inputHeight);

        cout << "Finding image matches..." << endl;
        vector<RGBImage*> outputImages;
        vector<RGB*> avgs;
        for (auto& img : inputImages) {
            avgs.push_back(getAverageRGB(img));
        }
        for (auto& targetImg : targetImages) {
            RGB* avg = getAverageRGB(*targetImg);
            int matchIndex = getBestMatchIndex(*avg, avgs);
            outputImages.push_back(&inputImages[matchIndex]);
            delete avg;  // Clean up the dynamically allocated average RGB
        }
        int rows = targetImage.get_height() / inputHeight;
        int cols = targetImage.get_width() / inputWidth;
        cout << "Rows: " << rows << ", Cols: " << cols << endl;
        cout << "Creating mosaic..." << endl;
        RGBImage mosaicImage = createImageGrid(outputImages, rows, cols);
        mosaicImage.DumpImage("colored_mosaic.jpg");
        LoadImage("colored_mosaic.jpg");

        // Clean up the targetImages
        for (auto& img : targetImages) {
            delete img;
        }

        // Clean up the average RGB pointers
        for (auto& avg : avgs) {
            delete avg;
        }
    } else {
        GrayImage targetImage;
        targetImage.LoadImage(targetImagePath);
        vector<GrayImage> inputImages = getGrayImages(inputFolderPath);
        int inputWidth = inputImages[0].get_width();
        int inputHeight = inputImages[0].get_height();
        cout << "Input image dimensions: " << inputWidth << "x" << inputHeight << endl;

        cout << "Splitting input image..." << endl;  
        vector<GrayImage*> targetImages = splitImage(targetImage, inputWidth, inputHeight);

        cout << "Finding image matches..." << endl;
        vector<GrayImage*> outputImages;
        vector<int*> avgs;
        for (auto& img : inputImages) {
            avgs.push_back(getAverageGray(img));
        }
        for (auto& targetImg : targetImages) {
            int* avg = getAverageGray(*targetImg);
            int matchIndex = getBestMatchIndex(*avg, avgs);
            outputImages.push_back(&inputImages[matchIndex]);
            delete avg;
        }
        int rows = targetImage.get_height() / inputHeight;
        int cols = targetImage.get_width() / inputWidth;
        cout << "Rows: " << rows << ", Cols: " << cols << endl;
        cout << "Creating mosaic..." << endl;
        RGBImage mosaicImage = createImageGrid(outputImages, rows, cols);
        mosaicImage.DumpImage("gray_mosaic.jpg");
        LoadImage("gray_mosaic.jpg");


        // Clean up the targetImages
        for (auto& img : targetImages) {
            delete img;
        }

        // Clean up the average gray pointers
        for (auto& avg : avgs) {
            delete avg;
        }
    }
}