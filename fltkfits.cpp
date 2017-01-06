#include "fltkfits.h"
#include "imagedisplay.h"
#include "histogramdisplay.h"

#include <CCfits/CCfits>
using namespace CCfits;


CImg<double> readImage(const char* filename) {
    std::valarray<double> contents;
    FITS pInfile(filename, Read, true);
    PHDU& primary_HDU = pInfile.pHDU();

    primary_HDU.read(contents);

    auto x = primary_HDU.axis(0);
    auto y = primary_HDU.axis(1);

    return CImg<double>(&contents[0], x, y, 1, 1, false);
}


fltkfits::fltkfits(char* filename) {
    auto image = readImage("test.fits");

    Fl_Window window(800, 500);

    ImageDisplay imdisplay(image, window.w()-200, window.h()-50);
    window.add(&imdisplay);

    HistogramDisplay histdisplay(image, &window, &imdisplay);
    window.add(&histdisplay);

    window.show();
    Fl::run();
}
