#include "MiniMap.h"
#include "ImageWidget.h"
#include <iostream>

MiniMap::MiniMap(Fl_Window* window) : Fl_Box(window->w()-200, 0, 200, 200){
    this->window = window;
}

void MiniMap::set_imagedisplay(ImageWidget* imagedisplay) {
    this -> imagedisplay = imagedisplay;
}

void MiniMap::set_image(CImg<double>& image) {
    original_width = image.width();
    original_height = image.height();
    this->image = image.get_resize(200, 200);
    redraw();
}

void MiniMap::draw() {

    if (this->image.size() == 0) {
        fl_draw_box(FL_FLAT_BOX, 0, 0, w(), h(), fl_rgb_color(0));
    }
    else {
        if (clip) {
            auto old = clipped;
            clipped = (image.get_cut(black, white) - black).normalize(0, 255);
            if (not move) { // Draw changes only if we don't have to erase the rectangle
                draw_changed(old, clipped, window->w() - 200, 0, 200, 200);
            }
        }
        if (move) { // This is a different form of draw_changed
            if (damaged_pixels.size() == 0) {
                fl_draw_image_mono(clipped.data(), window->w()-200, 0, 200, 200);
            }
            else {
                fl_color(damaged_pixels[0].color, damaged_pixels[0].color, damaged_pixels[0].color);
                fl_point(damaged_pixels[0].x, damaged_pixels[0].y);
                for (auto i = 1; i < damaged_pixels.size(); i++) {
                    if (damaged_pixels[i].color != damaged_pixels[i - 1].color) {
                        fl_color(damaged_pixels[i].color, damaged_pixels[i].color, damaged_pixels[i].color);
                    }
                    fl_point(damaged_pixels[i].x, damaged_pixels[i].y);
                }
            }
        }

        int x0 = round(600. + (double)x*200/original_width);
        int y0 = round((double)y * 200/original_height);
        int x1 = round(x0 + (600.0 * 200/original_width));
        int y1 = round(y0 + (450.0 * 200/original_height));

        fl_color(fl_rgb_color(255, 0, 0));
        fl_rect(x0, y0, x1-x0+1, y1-y0+1);

        damaged_pixels.clear();
        for (auto i = x0; i <= x1; i++) {
            damaged_pixels.push_back({i, y0, clipped(i-600, y0)});
            damaged_pixels.push_back({i, y1, clipped(i-600, y1)});
        }
        for (auto i = y0; i <= y1; i++) {
            damaged_pixels.push_back({x0, i, clipped(x0-600, i)});
            damaged_pixels.push_back({x1, i, clipped(x1-600, i)});
        }
        std::sort(damaged_pixels.begin(), damaged_pixels.end(), pixel_compare);

        clip = false;
        move = false;
    }
}

int MiniMap::handle(int event) {

    if (event == FL_FOCUS) {
        return 1;
    } else if (event == FL_PUSH or event == FL_DRAG or event == FL_RELEASE) {
        int map_x = (Fl::event_x() - 600) * original_width/200.0 - imagedisplay->w()/2;
        int map_y = Fl::event_y()*original_height/200.0 - imagedisplay->h()/2;

        map_x = std::max(0, std::min(map_x, original_width-imagedisplay->w()));
        map_y = std::max(0, std::min(map_y, original_height-imagedisplay->h()));

        set_origin(map_x, map_y);

        if (event == FL_RELEASE) {
            imagedisplay->set_origin(map_x, map_y);
        }
        return 1;
    }

    return 0;
}

void MiniMap::set_white(double white) {
    this -> white = white;
    clip = true;
    redraw();
}

void MiniMap::set_black(double black) {
    this -> black = black;
    clip = true;
    redraw();
}

void MiniMap::set_origin(int new_x, int new_y) {
    if (new_x != x or new_y != y) {
        x = new_x;
        y = new_y;
        move = true;
        redraw();
    }
}

