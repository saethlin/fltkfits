#ifndef FLTKFITS_IMAGEDISPLAY_H
#define FLTKFITS_IMAGEDISPLAY_H

#include <vector>
#include <algorithm>

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
#include <FL/x.H>

#include "CImg.h"
using namespace cimg_library;

#include "draw_changed.h"

class HistogramDisplay;
class MiniMap;
class DirList;
class CursorDisplay;

class ImageDisplay : public Fl_Box {
public:
    ImageDisplay(Fl_Window* window);
    void set_image(CImg<double>&);
    void set_minimap(MiniMap* minimap);
    void draw() override;
    void add(MiniMap* minimap);
    void add(HistogramDisplay* histogramdisplay);
    void add(DirList* dirlist);
    void add(CursorDisplay* cursordisplay);
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
    HistogramDisplay* histogramdisplay;
    CursorDisplay* cursordisplay;
};


#endif //FLTKFITS_IMAGEDISPLAY_H
