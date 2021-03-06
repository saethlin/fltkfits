//
// Created by ben on 1/14/17.
//

#ifndef FLTKFITS_CURSORDISPLAY_H
#define FLTKFITS_CURSORDISPLAY_H

#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>

#include <CImg.h>
using namespace cimg_library;

#include "draw_changed.h"

class CursorTracker : public Fl_Widget {
public:
    CursorTracker(Fl_Window* window);
    void set_display(int x, int y, double value);
    void draw() override;
    void resize(int x, int y, int w, int h) override;

private:
    CImg<uchar> image;
    int x = 0;
    int y = 0;
    double value = 0;
};


#endif //FLTKFITS_CURSORDISPLAY_H
