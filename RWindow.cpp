//
// Created by ben on 1/16/17.
//

#include "RWindow.h"


RWindow::RWindow(int w, int h) : Fl_Window(w, h) {
    last_width = w;
    last_height = h;
}


void RWindow::draw() {
    if (w() != last_width or h() != last_height) {
        for (auto i = 0; i < children(); i++) {
            child(i)->set_changed();
        }
        last_width = w();
        last_height = h();
    }
    Fl_Window::draw();
}


void RWindow::size_range(int minw, int minh, int maxw, int maxh) {
    Fl_Window::size_range(minw, minh, maxw, maxh);
}
