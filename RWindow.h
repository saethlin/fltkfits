//
// Created by ben on 1/16/17.
//

#ifndef FLTKFITS_RWINDOW_H
#define FLTKFITS_RWINDOW_H

#include <FL/Fl_Window.H>

class RWindow : public Fl_Window {
public:
    RWindow(int w, int h);
    void draw() override;
    void size_range(int X, int Y, int W, int H);
private:
    int last_width, last_height;
};


#endif //FLTKFITS_RWINDOW_H
