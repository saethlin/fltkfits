#ifndef FLTKFITS_IMAGEDISPLAY_H
#define FLTKFITS_IMAGEDISPLAY_H

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>

#include "CImg.h"
using namespace cimg_library;

#include "MiniMap.h"

class ImageDisplay : public Fl_Box {
public:
    ImageDisplay(CImg<double>& image, int width, int height);
    void set_minimap(MiniMap* minimap);
    void draw();
    void set_white(double white);
    void set_black(double black);
    void set_origin(int x, int  y);
    void set_zoom(double zoom);
    int handle(int event);
    double get_white();
    double get_black();

private:
    CImg<double> image;
    CImg<uchar> clipped;
    CImg<uchar> cropped;
    bool clip, move;
    double black, white;
    int x, y, width, height;
    int last_y, last_x;
    MiniMap* minimap;
};


#endif //FLTKFITS_IMAGEDISPLAY_H
