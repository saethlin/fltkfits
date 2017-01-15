#ifndef FLTKFITS_DIRLIST_H
#define FLTKFITS_DIRLIST_H

#include <FL/Fl.H>
#include <FL/Fl_File_Browser.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>

class ImageWidget;

class DirList : public Fl_File_Browser {
public:
    DirList(Fl_Window* window);
    void set_imagedisplay(ImageWidget* imagedisplay);
    int handle(int event) override;
private:
    ImageWidget* imagedisplay;
};


#endif //FLTKFITS_DIRLIST_H
