#ifndef FLTKFITS_DRAW_CHANGED_H
#define FLTKFITS_DRAW_CHANGED_H

#include <vector>
#include <algorithm>

#include <FL/fl_draw.H>
#include <CImg.h>
using namespace cimg_library;

typedef struct pixel {
    int x;
    int y;
    uchar color;
} pixel;

bool pixel_compare(const pixel& lhs, const pixel& rhs);

void draw_changed(CImg<uchar>& old, CImg<uchar>& fresh, int x0, int y0, int width, int height);

#endif //FLTKFITS_DRAW_CHANGED_H
