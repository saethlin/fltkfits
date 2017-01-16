#include "CursorTracker.h"
#include <sstream>

CursorTracker::CursorTracker(Fl_Window* window) : Fl_Widget(window->w()-200, 200, 200, 40) {}


void CursorTracker::resize(int x, int y, int w, int h) {
    Fl_Widget::resize(x, Fl_Widget::y(), this->w(), this->h());
}


void CursorTracker::set_display(int x, int y, double value) {
    this->x = x;
    this->y = y;
    this->value = value;
    redraw();
}


void CursorTracker::draw() {
    const uchar black[] = {0};
    const uchar white[] = {255};
    auto my_font = CImgList<uchar>::font(53, true);

    auto old = image;
    image = CImg<uchar>(w()*53./20., h()*53./20., 1, 1, 255);
    std::stringstream ss;

    ss << "X: " << x;
    image.draw_text(0, 0, ss.str().c_str(), black, white, 1.0, my_font);
    ss.str("");
    ss.clear();

    ss << "Y: "<< y;
    image.draw_text(image.width()/2, 0, ss.str().c_str(), black, white, 1.0, my_font);
    ss.str("");
    ss.clear();

    ss << "Value: " << value;
    image.draw_text(0, image.height()/2, ss.str().c_str(), black, white, 1.0, my_font);

    image.resize(w(), h(), -100, -100, 5);

    if (old.size() == 0 or changed()) {
        fl_draw_image_mono(image.data(), window()->w()-200, 200, image.width(), image.height());
        clear_changed();
    }
    else {
        draw_changed(old, image, window()->w()-200, 200, image.width()-1, image.height()-1);
    }
}
