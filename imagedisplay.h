#ifndef FLTKFITS_IMAGEDISPLAY_H
#define FLTKFITS_IMAGEDISPLAY_H

#include <valarray>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>

#include "CImg.h"
using namespace cimg_library;

class ImageDisplay : public Fl_Box {
public:
    ImageDisplay(CImg<double>& image);
    void draw();
    void set_white(double white);
    void set_black(double black);
    void set_origin(int x, int  y);
    int handle(int event);

private:
    std::valarray<double> image;
    uchar* bytesdata;
    bool reclip;
    double black, white;
};


#endif //FLTKFITS_IMAGEDISPLAY_H
