#include "gray_image.h"

#include <bits/stdc++.h>
using namespace std;

GrayImage::GrayImage() : Image(0, 0), pixels(nullptr) {}

GrayImage::GrayImage(int width, int height) : Image(width, height) {
    allocate_pixels(width, height);
}

GrayImage::GrayImage(int width, int height, int **pixels) : Image(width, height), pixels(pixels) {}

void GrayImage::allocate_pixels(int width, int height) {
    pixels = new int*[height];
    for (int i = 0; i < height; ++i) {
        pixels[i] = new int[width];
    }
}

GrayImage::GrayImage(const GrayImage& other) : Image(other.width, other.height) {
    allocate_pixels(other.width, other.height);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            pixels[i][j] = other.pixels[i][j];
        }
    }
}

GrayImage::~GrayImage() {
    if (pixels) {
        for (int i = 0; i < height; ++i) {
            delete[] pixels[i];
        }
        delete[] pixels;
    }
}

GrayImage& GrayImage::operator=(const GrayImage& other) {
    if (this == &other) {
        return *this;
    }

    width = other.width;
    height = other.height;
    allocate_pixels(other.width, other.height);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            pixels[i][j] = other.pixels[i][j];
        }
    }
    return *this;
}

bool GrayImage::LoadImage(const string& filename) {
    pixels = data_loader.Load_Gray(filename, &width, &height);
    return (pixels != nullptr);
}

void GrayImage::DumpImage(const string& filename) {
    data_loader.Dump_Gray(width, height, pixels, filename);
}

void GrayImage::Display_X_Server() {
    data_loader.Display_Gray_X_Server(width, height, pixels);
}

void GrayImage::Display_ASCII() {
    data_loader.Display_Gray_ASCII(width, height, pixels);
}

void GrayImage::Display_CMD() {
    string tempFilename = "temp.jpg";
    data_loader.Dump_Gray(width, height, pixels, tempFilename);
    data_loader.Display_Gray_CMD(tempFilename);
    string command = string("rm ") + tempFilename;
    system(command.c_str());
}

GrayImage GrayImage::crop(int startX, int startY, int crop_width, int crop_height) {
    GrayImage cropped_image(crop_width, crop_height);
    //cout << "Cropping from (" << startX << ", " << startY << ") with size (" << crop_width << ", " << crop_height << ")" << endl;
    for (int y = 0; y < crop_height; ++y) {
        for (int x = 0; x < crop_width; ++x) {
            if ((startY + y) < height && (startX + x) < width) {
                if (pixels[startY + y] != nullptr) {
                    //cout << "Accessing pixels[" << startY + y << "][" << startX + x << "]" << endl;
                    cropped_image.pixels[y][x] = pixels[startY + y][startX + x];
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

