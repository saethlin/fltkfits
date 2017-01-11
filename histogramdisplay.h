#ifndef FLTKFITS_HISTOGRAMDISPLAY_H
#define FLTKFITS_HISTOGRAMDISPLAY_H


#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>

#include "CImg.h"
using namespace cimg_library;

#include "imagedisplay.h"

#define NONE 0
#define WHITE 1
#define BLACK 2

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
    double black_slider, white_slider;
    int black_pos, white_pos;
    int new_black_pos, new_white_pos;
public:
    ~HistogramDisplay() override;

private:
    int clicked;
};


#endif //FLTKFITS_HISTOGRAMDISPLAY_H
