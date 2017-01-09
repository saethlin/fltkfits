#ifndef FLTKFITS_MNIIMAP_H
#define FLTKFITS_MNIIMAP_H

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>

#include "CImg.h"
using namespace cimg_library;

class MiniMap : public Fl_Box {
public:
    MiniMap(CImg<double>& image, Fl_Window* window);
    void draw();
    void set_black(double black);
    void set_white(double white);
    void set_width(int width);
    void set_height(int height);
    void set_zoom(double zoom);
    int handle(int event);
private:
    CImg<double> image;
    CImg<uchar> clipped;
    double black, white;
    int x, y, width, height;
    Fl_Window* window;
};


#endif //FLTKFITS_MNIIMAP_H
