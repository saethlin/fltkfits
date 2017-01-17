#ifndef FLTKFITS_REVERSIBLEIMAGE_H
#define FLTKFITS_REVERSIBLEIMAGE_H

#include <FL/fl_draw.H>

#include <CImg.h>
using namespace cimg_library;


class ReversibleImage : public CImg<uchar> {
public:
    ReversibleImage(uchar* data, int width, int height);
    void draw_image(CImg<uchar> new_image);
    void draw_line(int x0, int y0, int x1, int y1, const uchar* color);
    void revert();
    void flush(int x, int y);
private:
    std::vector<pixel> changed;
};


struct pixel {
    int x;
    int y;
    uchar color;
    bool operator<(const pixel& lhs const pixel& rhs) const {
        return lhs.color < rhs.color;
    }
};


#endif //FLTKFITS_REVERSIBLEIMAGE_H
