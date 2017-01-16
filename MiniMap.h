#ifndef FLTKFITS_MNIIMAP_H
#define FLTKFITS_MNIIMAP_H

#include <vector>
#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>

#include "CImg.h"
using namespace cimg_library;

#include "draw_changed.h"

class ImageWidget;

class MiniMap : public Fl_Widget {
public:
    MiniMap(Fl_Window* window);
    void set_imagedisplay(ImageWidget* imagedisplay);
    void draw();
    void set_image(CImg<double>& image);
    void set_black(double black);
    void set_white(double white);
    void set_width(int width);
    void set_height(int height);
    void set_origin(int x, int y);
    void set_zoom(double zoom);
    int handle(int event);
private:
    CImg<double> image;
    CImg<uchar> clipped;
    double black, white;
    int x, y, last_x, last_y;
    bool clip, move;
    int original_width, original_height;
    std::vector<pixel> damaged_pixels;

    Fl_Window* window;
    ImageWidget* imagedisplay;
};


#endif //FLTKFITS_MNIIMAP_H
