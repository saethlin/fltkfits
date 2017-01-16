#ifndef FLTKFITS_IMAGEDISPLAY_H
#define FLTKFITS_IMAGEDISPLAY_H

#include <vector>
#include <algorithm>

#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
//#include <FL/x.H>

#include "CImg.h"
using namespace cimg_library;

#include "draw_changed.h"

class HistogramWidget;
class MiniMap;
class DirList;
class CursorTracker;

class ImageWidget : public Fl_Widget {
public:
    ImageWidget(Fl_Window* window);
    void set_image(CImg<double>&);
    void set_minimap(MiniMap* minimap);
    void draw() override;
    void add(MiniMap* minimap);
    void add(HistogramWidget* histogramdisplay);
    void add(DirList* dirlist);
    void add(CursorTracker* cursordisplay);
    void set_white(double white);
    void set_black(double black);
    void set_origin(int x, int  y);
    void set_zoom(double zoom);
    int handle(int event) override;
    double get_white();
    double get_black();

private:
    CImg<double> image;
    CImg<uchar> clipped;
    CImg<uchar> cropped;
    bool clip, move;
    double black, white;
    int x, y, cursor_x, cursor_y;
    MiniMap* minimap;
    HistogramWidget* histogramdisplay;
    CursorTracker* cursordisplay;
};


#endif //FLTKFITS_IMAGEDISPLAY_H
