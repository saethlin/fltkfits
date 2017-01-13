#include "imagedisplay.h"
#include "histogramdisplay.h"
#include "MiniMap.h"

#include <CCfits/CCfits>
using namespace CCfits;


CImg<double> readImage(const char* filename) {
    std::valarray<double> contents;
    FITS pInfile(filename, Read, true);
    PHDU& primary_HDU = pInfile.pHDU();

    primary_HDU.read(contents);

    auto x = primary_HDU.axis(0);
    auto y = primary_HDU.axis(1);

    return CImg<double>(&contents[0], x, y);
}

int main(int argc, char* argv[]) {
    Fl_Window window(800, 500);

    ImageDisplay imdisplay(&window);
    window.add(&imdisplay);

    HistogramDisplay histdisplay(&window, &imdisplay);
    window.add(&histdisplay);

    MiniMap minimap(&window);
    window.add(&minimap);
    imdisplay.add(&minimap);

    if (argc > 1) {
        auto image = readImage(argv[1]);
        imdisplay.set_image(image);
        histdisplay.set_image(image);
    }

    window.show();
    Fl::run();
}