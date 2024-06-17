#include "image.h"
#include "data_loader.h"

#include <bits/stdc++.h>
using namespace std;

Image::Image(int width, int height) : width(width), height(height) {}

Image::~Image() {
}

int Image::get_width() const {
    return width;
}

int Image::get_height() const {
    return height;
}