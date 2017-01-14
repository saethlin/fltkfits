#include "CursorDisplay.h"
#include <iostream>
#include <sstream>

CursorDisplay::CursorDisplay(Fl_Window *window) : Fl_Box(window->w()-200, 200, 200, 20) {}


void CursorDisplay::set_display(int x, int y, double value) {
    this->x = x;
    this->y = y;
    this->value = value;
    redraw();
}


void CursorDisplay::draw() {
    const uchar black[] = {0};
    auto old = image;
    image = CImg<uchar>(w(), h(), 1, 1, 255);
    std::stringstream ss;
    ss << x << " " << y << " " << value;
    image.draw_text(0, 0, ss.str().c_str(), black);

    if (old.size() == 0) {
        fl_draw_image_mono(image.data(), window()->w()-200, 200, image.width(), image.height());
    }
    else {
        draw_changed(old, image, window()->w()-200, 200, image.width()-1, image.height()-1);
    }
}

int CursorDisplay::handle(int event) {
    return 0;
}
