#include "imagedisplay.h"
#include "histogramdisplay.h"
#include "MiniMap.h"
#include "DirList.h"

ImageDisplay::ImageDisplay(Fl_Window* window) : Fl_Box(0, 0, window->w()-200, window->h()-50) {}


void ImageDisplay::add(HistogramDisplay* histogramdisplay) {
    this->histogramdisplay = histogramdisplay;
    histogramdisplay->set_imagedisplay(this);
}


void ImageDisplay::add(MiniMap* minimap) {
    this -> minimap = minimap;
}


void ImageDisplay::add(DirList* dirlist) {
    dirlist -> set_imagedisplay(this);
}


void ImageDisplay::set_image(CImg<double>& image) {
    this -> image = image;
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


typedef struct pixel{
    int x;
    int y;
    uchar color;
} pixel;


bool acompare(const pixel& lhs, const pixel& rhs) {
    return lhs.color < rhs.color;
}


void ImageDisplay::draw() {
    if (this->image.size() == 0) {
        fl_draw_box(FL_FLAT_BOX, 0, 0, w(), h(), fl_rgb_color(0));
    }
    else {
        auto old = cropped;
        if (clip) {
            clipped = (image.get_cut(black, white) - black).normalize(0, 255);
            move = true;
        }

        if (move) {
            cropped = clipped.get_crop(x, y, x + w(), y + h(), 0);
        }

        clip = false;
        move = false;

        std::vector<pixel> changed;
        for (auto y = 0; y < this->h(); y++) {
            for (auto x = 0; x < this->w(); x++) {
                if (x >= old.width() or y >= old.height() or old(x, y) != cropped(x, y)) {
                    changed.push_back({x, y, cropped(x, y)});
                }
            }
        }

        std::sort(changed.begin(), changed.end(), acompare);

        fl_color(changed[0].color, changed[0].color, changed[0].color);
        fl_point(changed[0].x, changed[0].y);
        for (auto i = 1; i < changed.size(); i++) {
            if (changed[i].color != changed[i - 1].color) {
                fl_color(changed[i].color, changed[i].color, changed[i].color);
            }
            fl_point(changed[i].x, changed[i].y);
        }
    }
}

void ImageDisplay::set_white(double white) {
    if (white != this->white) {
        this->white = white;
        clip = true;
        redraw();
        if (minimap != NULL) {
            minimap->set_white(white);
        }
    }
}

void ImageDisplay::set_black(double black) {
    if (black != this->black) {
        this->black = black;
        clip = true;
        redraw();
        if (minimap != NULL) {
            minimap->set_black(black);
        }
    }
}

double ImageDisplay::get_white() {
    return white;
}

double ImageDisplay::get_black() {
    return black;
}

void ImageDisplay::set_origin(int x, int y) {

    auto try_x = std::min(image.width() - this->w(), std::max(x, 0));
    auto try_y = std::min(image.height() - this->h(), std::max(y, 0));

    if ((try_x != this->x) || (try_y != this->y)) {
        this -> x = try_x;
        this -> y = try_y;
        move = true;
        redraw();
    }

}

void ImageDisplay::set_zoom(double zoom) {
    //get_resize_halfXY()
    //get_resize_doubleXY()
    //get_resize()
}

int ImageDisplay::handle(int event) {

    if (event == FL_FOCUS or event == FL_UNFOCUS) {
        return 1;
    } else if (event == FL_PUSH) {
        last_y = Fl::event_y();
        last_x = Fl::event_x();
        return 1;
    } else if (event == FL_DRAG) {
        set_origin(x + (last_x - Fl::event_x()), y + (last_y - Fl::event_y()));
        last_x = Fl::event_x();
        last_y = Fl::event_y();
        return 1;
    }

    return 0;
}

void ImageDisplay::set_minimap(MiniMap* minimap) {
    this -> minimap = minimap;
}
