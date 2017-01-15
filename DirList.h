#ifndef FLTKFITS_DIRLIST_H
#define FLTKFITS_DIRLIST_H

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>

class ImageWidget;

class DirList : public Fl_Box {
public:
    DirList(Fl_Window* window);
    void set_imagedisplay(ImageWidget* imagedisplay);

private:
    Fl_Window* window;
    ImageWidget* imagedisplay;
};


#endif //FLTKFITS_DIRLIST_H
