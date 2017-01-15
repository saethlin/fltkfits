#include "DirList.h"
#include <iostream>


DirList::DirList(Fl_Window* window) : Fl_File_Browser(window->w()-200, 240, 200, window->h()-240) {
    load(".");
    value(1);
}


void DirList::set_imagedisplay(ImageWidget* imagedisplay) {
    this -> imagedisplay = imagedisplay;
}


int DirList::handle(int event) {
    if (event == FL_FOCUS or event == FL_UNFOCUS) {
        return 1;
    }
    if (event == FL_KEYDOWN) {
        if (Fl::event_key() == FL_Down) {
            value(value()+1);
            return 1;
        }
        else if (Fl::event_key() == FL_Up) {
            value(value()-1);
            return 1;
        }
        else if (Fl::event_key() == FL_Right or Fl::event_key() == FL_Enter) {
            // Open or change directory to
        }
        else if (Fl::event_key() == FL_Left or Fl::event_key() == FL_BackSpace) {
            // Move back one level in the path
        }
    }
    return 0;
}
