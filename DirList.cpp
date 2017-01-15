#include "DirList.h"

DirList::DirList(Fl_Window* window) : Fl_Box(window->w()-200, 200, 200, window->h()-250) {
    this -> window = window;
}

void DirList::set_imagedisplay(ImageWidget* imagedisplay) {
    this -> imagedisplay = imagedisplay;
}
