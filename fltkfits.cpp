//
// Created by ben on 1/3/17.
//

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
#include "fltkfits.h"
#include "ImageDisplay.h"

#include <CCfits/CCfits>
using namespace CCfits;


typedef struct {
    std::valarray<double> data;
    long x;
    long y;
} ImageStruct;


ImageStruct readImage(const char* filename) {
    std::valarray<double> contents;
    FITS pInfile(filename, Read, true);
    PHDU& primary_HDU = pInfile.pHDU();

    primary_HDU.read(contents);

    auto x = primary_HDU.axis(0);
    auto y = primary_HDU.axis(1);

    return ImageStruct{contents, x, y};
}


fltkfits::fltkfits(char* filename) {
    auto contents = readImage(filename);

}


int main() {
    auto image_struct = readImage("test.fits");

    Fl_Window window(image_struct.x, image_struct.y);
    ImageDisplay imdisplay(image_struct.data);
    window.add(&imdisplay);
    window.show();
    return Fl::run();
}
