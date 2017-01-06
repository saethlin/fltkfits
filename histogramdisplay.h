#ifndef FLTKFITS_HISTOGRAMDISPLAY_H
#define FLTKFITS_HISTOGRAMDISPLAY_H


#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>

#include "CImg.h"
using namespace cimg_library;

#include "imagedisplay.h"

class HistogramDisplay : public Fl_Box {
public:
    HistogramDisplay(CImg<double>& image, Fl_Window* window, ImageDisplay* display);
    void draw();
    int handle(int event);

private:
    CImg<uchar> histogram;
    CImg<uchar> scaled;
    std::vector<double> histogram_to_value;
    Fl_Window* window;
    ImageDisplay* imagedisplay;
    int width;
    double black_slider, white_slider;
};


#endif //FLTKFITS_HISTOGRAMDISPLAY_H
