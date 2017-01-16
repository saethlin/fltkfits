#include "ImageWidget.h"
#include "HistogramWidget.h"
#include "MiniMap.h"
#include "DirList.h"
#include "CursorTracker.h"
#include "RWindow.h"

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
    RWindow window(800, 500);

    ImageWidget imdisplay(&window);
    window.add(&imdisplay);

    HistogramWidget histogram(&window);
    window.add(&histogram);

    DirList dirlist(&window);
    window.add(dirlist);

    MiniMap minimap(&window);
    window.add(&minimap);

    CursorTracker cursor(&window);
    window.add(&cursor);
    Fl::focus(&cursor);

    imdisplay.add(&histogram);
    imdisplay.add(&minimap);
    imdisplay.add(&dirlist);
    imdisplay.add(&cursor);

    window.resizable(imdisplay);

    if (argc > 1) {
        auto image = readImage(argv[1]);
        window.size_range(0, 0, image.width()+200, image.height()+50);
        imdisplay.set_image(image);
    }

    window.show();
    Fl::run();
}