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
    HistogramDisplay(Fl_Window* window, ImageDisplay* display);
    void draw() override;
    int handle(int event) override;
    void set_image(CImg<double>& image);

private:
    CImg<uchar> histogram;
    CImg<uchar> scaled;
    std::vector<double> histogram_to_value;
    Fl_Window* window;
    ImageDisplay* imagedisplay;
    double black_slider, white_slider;
    int black_pos, white_pos;
    int new_black_pos, new_white_pos;
    int clicked;
public:
    ~HistogramDisplay() override;
};


#endif //FLTKFITS_HISTOGRAMDISPLAY_H
