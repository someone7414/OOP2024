#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "data_loader.h"

#include <bits/stdc++.h>
using namespace std;

class Image {
protected:
    int width;
    int height;
    static Data_Loader data_loader;
public:
    Image(int width, int height);
    virtual ~Image();
    virtual bool LoadImage(const string& filename) = 0;
    virtual void DumpImage(const string& filename) = 0;
    virtual void Display_X_Server() = 0;
    virtual void Display_ASCII() = 0;
    virtual void Display_CMD() = 0;
    int get_width() const;
    int get_height() const;
};

#endif // IMAGE_H
