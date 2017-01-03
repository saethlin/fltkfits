//
// Created by ben on 1/3/17.
//

#ifndef FLTKFITS_IMAGEDISPLAY_H
#define FLTKFITS_IMAGEDISPLAY_H

#include <valarray>
#include <FL/Fl_Box.H>

class ImageDisplay : public Fl_Box {
public:
    ImageDisplay(std::valarray<double>& image);
    void draw();
    void set_white(double white);
    void set_black(double black);
    void set_origin(int x, int  y);
    int handle(int event);

private:
    std::valarray<double> image;
    uchar* bytesdata;
    bool reclip;
    double black, white;
};


#endif //FLTKFITS_IMAGEDISPLAY_H
