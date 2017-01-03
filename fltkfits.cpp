#include "fltkfits.h"
#include "imagedisplay.h"

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

    auto image = CImg(&contents[0], x, y, 1, 1, false);

    return ImageStruct{contents, x, y};
}


fltkfits::fltkfits(char* filename) {
    auto image_struct = readImage("test.fits");

    Fl_Window window(image_struct.x, image_struct.y);
    ImageDisplay imdisplay(image_struct.data);
    window.add(&imdisplay);
    window.show();
    Fl::run();
}
