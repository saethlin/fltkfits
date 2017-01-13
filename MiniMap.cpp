#include "MiniMap.h"

MiniMap::MiniMap(Fl_Window* window) : Fl_Box(window->w()-200, 0, 200, 200){
    this->window = window;
}

void MiniMap::set_image(CImg<double>& image) {
    this->image = image.get_resize(200, 200);
}

void MiniMap::draw() {

    if (this->image.size() == 0) {
        fl_draw_box(FL_FLAT_BOX, 0, 0, w(), h(), fl_rgb_color(0));
    }
    else {
        if (clip) {
            clipped = (image.get_cut(black, white) - black).normalize(0, 255);
            fl_draw_image_mono(clipped.data(), window->w() - 200, 0, 200, 200);
            move = true;
        }
        if (move) {

        }
        clip = false;
        move = false;
    }
}

int MiniMap::handle(int event) {
    return 0;
}

void MiniMap::set_white(double white) {
    this -> white = white;
    clip = true;
    redraw();
}

void MiniMap::set_black(double black) {
    this -> black = black;
    clip = true;
    redraw();
}

void MiniMap::set_origin(int new_x, int new_y) {
    if (new_x != x or new_y != y) {
        x = new_x;
        y = new_y;
        move = true;
    }
    redraw();
}
