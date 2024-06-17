#include "image.h"
#include "gray_image.h"
#include "rgb_image.h"
#include "photo_mosaic.h"
#include "bit_field_filter.h"

#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]){
    Image *img1 = new GrayImage();
    img1->LoadImage("Image-Folder/mnist/img_100.jpg");
    img1->DumpImage("img1.jpg");
    //img1->Display_X_Server();
    img1->Display_ASCII();
    img1->Display_CMD();
    delete img1;

    Image *img2 = new RGBImage();
    img2->LoadImage("Image-Folder/lena.jpg");
    img2->DumpImage("img2.jpg");
    //img2->Display_X_Server();
    img2->Display_ASCII();
    img2->Display_CMD();
    delete img2;

    // some bit field filter design driven code here
    GrayImage *img3;
    for(int i=0;i<8;i++){
        img3 = new GrayImage();
        img3->LoadImage("Image-Folder/"+to_string(i+1)+".jpg");
        cout<<"Original Image:"<<endl;
        img3->Display_CMD();
        applyFilters(img3, pow(2,i));
        img3->DumpImage("option"+to_string(i+1)+".jpg");
        //img3->Display_X_Server();
        img3->Display_CMD();
        delete img3;
    }
    
    img3 = new GrayImage();
    img3->LoadImage("Image-Folder/lena.jpg");
    cout<<"Original Image:"<<endl;
    img3->Display_CMD();
    GrayImage *upscaled = new GrayImage(img3->get_width()*10, img3->get_height()*10);
    upscaleImage(img3->get_width(), img3->get_height(), img3->get_pixels(), upscaled->get_width(), upscaled->get_height(), upscaled->get_pixels());
    upscaled->DumpImage("upscaled.jpg");
    //img3->Display_X_Server();
    upscaled->Display_CMD();
    delete img3;
    delete upscaled;

    RGBImage *img4;
    for(int i=8;i<12;i++){
        img4 = new RGBImage();
        img4->LoadImage("Image-Folder/test.jpg");
        cout<<"Original Image:"<<endl;
        img4->Display_CMD();
        applyFilters(img4, pow(2,i));
        img4->DumpImage("option"+to_string(i+1)+".jpg");
        //img4->Display_X_Server();
        img4->Display_CMD();
        delete img4;
    }

    // some photo mosaic driven code here
    PhotoMosaic *img5 = new PhotoMosaic();
    img5->createPhotomosaic("Image-Folder/girl_2x.png", "Image-Folder/mnist", 0);
    cout << "Photo mosaic created and saved as gray_mosaic.jpg" << endl;
    //img5->Display_X_Server();
    img5->Display_CMD();
    delete img5;

    PhotoMosaic *img6 = new PhotoMosaic();
    img6->createPhotomosaic("Image-Folder/girl_2x.png", "Image-Folder/cifar10", 1);
    cout << "Photo mosaic created and saved as colored_mosaic.jpg" << endl;
    //img6->Display_X_Server();
    img6->Display_CMD();
    delete img6;

    // more ...

    return 0;
}
