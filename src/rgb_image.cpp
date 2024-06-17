#include "rgb_image.h"

#include <bits/stdc++.h>
using namespace std;

RGBImage::RGBImage() : Image(0, 0), pixels(nullptr) {}

RGBImage::RGBImage(int width, int height) : Image(width, height) {
    allocate_pixels(width, height);
}

RGBImage::RGBImage(int width, int height, int ***pixels) : Image(width, height), pixels(pixels) {}

void RGBImage::allocate_pixels(int width, int height) {
    pixels = new int**[height];
    for (int i = 0; i < height; ++i) {
        pixels[i] = new int*[width];
        for (int j = 0; j < width; ++j) {
            pixels[i][j] = new int[3]();
        }
    }
}

RGBImage::RGBImage(const RGBImage &other) : Image(other.width, other.height) {
    allocate_pixels(other.width, other.height);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            for (int k = 0; k < 3; ++k) {
                pixels[i][j][k] = other.pixels[i][j][k];
            }
        }
    }
}

RGBImage::~RGBImage() {
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

RGBImage& RGBImage::operator=(const RGBImage &other) {
    if (this == &other) {
        return *this;
    }

    width = other.width;
    height = other.height;
    allocate_pixels(other.width, other.height);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            for (int k = 0; k < 3; ++k) {
                pixels[i][j][k] = other.pixels[i][j][k];
            }
        }
    }
    return *this;
}

bool RGBImage::LoadImage(const string& filename) {
    pixels = data_loader.Load_RGB(filename, &width, &height);
    return (pixels != nullptr);
}

void RGBImage::DumpImage(const string& filename) {
    data_loader.Dump_RGB(width, height, pixels, filename);
}

void RGBImage::Display_X_Server() {
    data_loader.Display_RGB_X_Server(width, height, pixels);
}

void RGBImage::Display_ASCII() {
    data_loader.Display_RGB_ASCII(width, height, pixels);
}

void RGBImage::Display_CMD() {
    string tempFilename = "temp.jpg";
    data_loader.Dump_RGB(width, height, pixels, tempFilename);
    data_loader.Display_RGB_CMD(tempFilename);
    string command = "rm " + tempFilename;
    system(command.c_str());
}

RGBImage RGBImage::crop(int startX, int startY, int crop_width, int crop_height) {
    RGBImage cropped_image(crop_width, crop_height);
    //cout << "Cropping from (" << startX << ", " << startY << ") with size (" << crop_width << ", " << crop_height << ")" << endl;
    for (int y = 0; y < crop_height; ++y) {
        for (int x = 0; x < crop_width; ++x) {
            if ((startY + y) < height && (startX + x) < width) {
                if (pixels[startY + y] != nullptr && pixels[startY + y][startX + x] != nullptr) {
                    //cout << "Accessing pixels[" << startY + y << "][" << startX + x << "]" << endl;
                    cropped_image.pixels[y][x][0] = pixels[startY + y][startX + x][0];
                    cropped_image.pixels[y][x][1] = pixels[startY + y][startX + x][1];
                    cropped_image.pixels[y][x][2] = pixels[startY + y][startX + x][2];
                } else {
                    cout << "Null pointer detected at pixels[" << startY + y << "][" << startX + x << "]" << endl;
                }
            } else {
                cout << "Out of bounds access: pixels[" << startY + y << "][" << startX + x << "]" << endl;
            }
        }
    }
    //cout << "Done cropping" << endl;
    return cropped_image;
}