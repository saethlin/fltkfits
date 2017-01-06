#include "imagedisplay.h"
#include <iostream>

ImageDisplay::ImageDisplay(CImg<double>& image, int width, int height) : Fl_Box(0, 0, width, height) {
    this -> image = image;
    this -> width = width;
    this -> height = height;
    set_origin(0, 0);

    // Initialize with nice black and white clipping values
    std::vector<double> sortable(image.data(), image.data() + image.size());
    auto median = sortable.begin() + (sortable.size()/2);
    auto white_level = sortable.begin() + sortable.size()*0.997;
    std::nth_element(sortable.begin(), median, sortable.end());
    std::nth_element(sortable.begin(), white_level, sortable.end());
    set_white(*white_level);
    set_black(*median);
}

void ImageDisplay::draw() {
    if (clip) {
        clipped = (image.get_cut(black, white) - black).normalize(0, 255);
        move = true;
    }

    if (move) {
        cropped = clipped.get_crop(x, y, x+width, y+width, 0);
    }

    clip = false;
    move = false;
    fl_draw_image_mono(cropped.data(), 0, 0, width+1, height+1);
}

void ImageDisplay::set_white(double white) {
    if (white != this->white) {
        this->white = white;
        clip = true;
        redraw();
    }
}

void ImageDisplay::set_black(double black) {
    if (black != this->black) {
        this->black = black;
        clip = true;
        redraw();
    }
}

double ImageDisplay::get_white() {
    return white;
}

double ImageDisplay::get_black() {
    return black;
}

// TODO: Better variable names in here
void ImageDisplay::set_origin(int x, int y) {

    auto try_x = std::min(image.width()-width, std::max(x, 0));
    auto try_y = std::min(image.height()-height, std::max(y, 0));

    if ((try_x != this->x) || (try_y != this->y)) {
        this -> x = try_x;
        this -> y = try_y;
        move = true;
        redraw();
    }

}

void ImageDisplay::set_zoom(double zoom) {
    //get_resize_halfXY()
    //get_resize_doubleXY()
    //get_resize()
}

int ImageDisplay::handle(int event) {

    if (event == FL_FOCUS or event == FL_UNFOCUS) {
        return 1;
    } else if (event == FL_PUSH) {
        last_y = Fl::event_y();
        last_x = Fl::event_x();
        return 1;
    } else if (event == FL_DRAG) {
        set_origin(x + (last_x - Fl::event_x()), y + (last_y - Fl::event_y()));
        last_x = Fl::event_x();
        last_y = Fl::event_y();
        return 1;
    }

    return 0;
}