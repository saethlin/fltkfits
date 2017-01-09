#include "MiniMap.h"

MiniMap::MiniMap(CImg<double>& image, Fl_Window* window) : Fl_Box(window->w()-200, 0, 200, 200){
    // Downsample the image
    this -> image = image.get_resize(200, 200);
    this -> window = window;
}

void MiniMap::draw() {
    clipped = (image.get_cut(black, white) - black).normalize(0, 255);
    fl_draw_image_mono(clipped.data(), window->w()-200, 0, 200, 200);
}

int MiniMap::handle(int event) {
    return 0;
}

void MiniMap::set_white(double white) {
    this -> white = white;
}

void MiniMap::set_black(double black) {
    this -> black = black;
}
