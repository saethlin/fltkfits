#include "ImageWidget.h"
#include "HistogramWidget.h"
#include "MiniMap.h"
#include "DirList.h"
#include "CursorTracker.h"


ImageWidget::ImageWidget(Fl_Window* window) : Fl_Widget(0, 0, window->w()-200, window->h()-50) {}


void ImageWidget::add(HistogramWidget* histogramdisplay) {
    this->histogramdisplay = histogramdisplay;
    histogramdisplay->set_imagedisplay(this);
}


void ImageWidget::add(MiniMap* minimap) {
    this->minimap = minimap;
    minimap->set_imagedisplay(this);
}


void ImageWidget::add(DirList* dirlist) {
    dirlist->set_imagedisplay(this);
}

void ImageWidget::add(CursorTracker* cursordisplay) {
    this->cursordisplay = cursordisplay;
}


void ImageWidget::set_image(CImg<double>& image) {
    this->image = image;
    set_origin(0, 0);

    // Initialize with nice black and white clipping values
    std::vector<double> sortable(image.data(), image.data() + image.size());
    auto median = sortable.begin() + (sortable.size()/2);
    auto white_level = sortable.begin() + sortable.size()*0.997;
    std::nth_element(sortable.begin(), median, sortable.end());
    std::nth_element(sortable.begin(), white_level, sortable.end());
    set_white(*white_level);
    set_black(*median);

    minimap->set_image(image);
    minimap->set_white(white);
    minimap->set_black(black);
    minimap->set_origin(x, y);

    histogramdisplay->set_image(image);
}


void ImageWidget::draw() {
    if (image.size() == 0) {
        fl_draw_box(FL_FLAT_BOX, 0, 0, w(), h(), fl_rgb_color(0));
    }
    else if (clip or move or changed()) {
        auto old = cropped;

        if (clip) {
            clipped = (image.get_cut(black, white) - black).normalize(0, 255);
            move = true;
        }

        if (move or changed()) {
            cropped = clipped.get_crop(x, y, x+w(), y+h());
        }
        clip = false;
        move = false;
        if (changed()) {
            fl_draw_image_mono(cropped.data(), 0, 0, w()+1, h());
            clear_changed();
        }
        else {
            draw_changed(old, cropped, 0, 0, w(), h());
        }
    }
}


void ImageWidget::set_white(double white) {
    if (white != this->white) {
        this->white = white;
        clip = true;
        redraw();
        if (minimap != NULL) {
            minimap->set_white(white);
        }
    }
}

void ImageWidget::set_black(double black) {
    if (black != this->black) {
        this->black = black;
        clip = true;
        redraw();
        if (minimap != NULL) {
            minimap->set_black(black);
        }
    }
}

double ImageWidget::get_white() {
    return white;
}

double ImageWidget::get_black() {
    return black;
}

void ImageWidget::set_origin(int x, int y) {

    auto try_x = std::min(image.width() - w(), std::max(x, 0));
    auto try_y = std::min(image.height() - h(), std::max(y, 0));

    if ((try_x != this->x) || (try_y != this->y)) {
        this->x = try_x;
        this->y = try_y;
        move = true;
        redraw();
    }

}

void ImageWidget::set_zoom(double zoom) {
    //get_resize_halfXY()
    //get_resize_doubleXY()
    //get_resize()
}

int ImageWidget::handle(int event) {
    if (event == FL_FOCUS || event == FL_ENTER || event == FL_PUSH) {
        return 1;
    }
    else if (event == FL_MOVE) {
        cursor_x = Fl::event_x() + x;
        cursor_y = Fl::event_y() + y;
        if (cursor_x < image.width() and cursor_y < image.height()) {
            cursordisplay->set_display(cursor_x, cursor_y, image(cursor_x, cursor_y));
        }
        return 1;
    }

    return 0;
}
