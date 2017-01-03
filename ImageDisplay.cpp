#include "ImageDisplay.h"

ImageDisplay::ImageDisplay(std::valarray<double>& image) : Fl_Box(0, 0, 1024, 1024) {
    this -> image = image;
    bytesdata = new uchar[image.size()];
    white = image.max();
    black = image.min();
    reclip = true;
}

void ImageDisplay::draw() {
    if (reclip) {
        for (auto i = 0; i < image.size(); i++) {
            auto tmp = std::min(white, std::max(image[i], black)) - black;
            bytesdata[i] = (uchar) (255 * tmp / white);
        }
        reclip = false;
    }

    fl_draw_image_mono(bytesdata, 0, 0, 1024, 1024);
}

void ImageDisplay::set_white(double white) {
    if (white != this->white) {
        this->white = white;
        reclip = true;
        redraw();
    }
}

void ImageDisplay::set_black(double black) {
    if (black != this->black) {
        this->black = black;
        reclip = true;
        redraw();
    }
}

int ImageDisplay::handle(int event) {
    if (event == FL_KEYUP) {
        if (Fl::event_key() == FL_Up) {
            set_white(this->white / 1.1);
            return 1;
        } else if (Fl::event_key() == FL_Down) {
            set_black(this->black *= 1.1);
            return 1;
        }
    }
    return 0;
}