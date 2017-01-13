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

    return CImg<double>(&contents[0], x, y, 1, 1, false);
}

// TODO: Determine if this is any better than the default implementation, it seems to
void Fl_Window::draw() {
    draw_children();
}

int main() {
    auto image = readImage("test.fits");

    Fl_Window window(800, 500);

    ImageDisplay imdisplay(&window);
    window.add(&imdisplay);

    HistogramDisplay histdisplay(&window, &imdisplay);
    window.add(&histdisplay);

    //MiniMap minimap(image, &window);
    //window.add(&minimap);

    //imdisplay.set_minimap(&minimap);

    imdisplay.set_image(image);
    histdisplay.set_image(image);

    window.show();
    Fl::run();
}