#include "histogramdisplay.h"
#include <iostream>
#include <math.h>


HistogramDisplay::HistogramDisplay(Fl_Window* window, ImageDisplay* imagedisplay) : Fl_Box(0, window->h()-50, window->w()-200, 50) {
    this->window = window;
    this->imagedisplay = imagedisplay;
}

void HistogramDisplay::set_image(CImg<double>& image) {
    std::vector<double> sortable(image.data(), image.data() + image.size());
    auto image_max = std::max_element(sortable.begin(), sortable.end());

    std::vector<int> bincount((unsigned long)(ceil(*image_max)));
    for (auto& val : sortable) {
        bincount[ceil(val)] += 1;
    }

    histogram_to_value = std::vector<double>();

    auto max_counts = std::max_element(bincount.begin(), bincount.end());
    auto max_count = *max_counts;

    auto data = std::vector<uchar>();
    data.reserve(bincount.size());

    double closest_black_distance = imagedisplay->get_black();
    double closest_white_distance = imagedisplay->get_white();
    black_slider = 0.0;
    white_slider = 0.0;

    for (auto i = 0; i < bincount.size(); i++) {
        auto val = bincount[i];
        if (val != 0) {

            histogram_to_value.push_back(i);
            data.push_back(50*(double)val/(double)max_count);

            auto test_black = fabs(i - imagedisplay->get_black());
            if (test_black < closest_black_distance) {
                closest_black_distance = test_black;
                black_slider = data.size();
            }

            auto test_white = fabs(i - imagedisplay->get_white());
            if (test_white < closest_white_distance) {
                closest_white_distance = test_white;
                white_slider = data.size();
            }

        }
    }

    // Create actual histogram image
    histogram = CImg<uchar>(data.size(), 50, 1, 1, 255);
    for (auto x = 0; x < data.size(); x++) {
        for (auto y = 50-data[x]; y < 50; y++) {
            histogram(x, y) = 0;
        }
    }

    clicked = NONE;

    redraw();

}

void HistogramDisplay::draw() {
    if (this->histogram.size() == 0) {
        fl_draw_box(FL_FLAT_BOX, 0, this->parent()->h()-h(), w(), h(), fl_rgb_color(255));
    }
    else if (window->w()-200 != scaled.width()) {
        scaled = histogram.get_resize(window->w()-200, 50, 1, 1, 1);
        black_pos = black_slider * scaled.width()/histogram.width();
        white_pos = white_slider * scaled.width()/histogram.width();
        new_black_pos = black_pos;
        new_white_pos = white_pos;
        fl_draw_image_mono(scaled.data(), 0, window->h()-50, scaled.width(), scaled.height()+1);
        fl_color(255, 0, 0);
        fl_line(black_pos, window->h(), black_pos, window->h() - 50);
        fl_line(white_pos, window->h(), white_pos, window->h() - 50);
    }
    else {
        fl_color(255, 0, 0);
        if (new_black_pos != black_pos) {
            auto column = scaled.get_column(black_pos);
            fl_draw_image_mono(column.data(), black_pos, window->h()-50, 1, 50);
            fl_line(new_black_pos, window->h(), new_black_pos, window->h() - 50);
            black_pos = new_black_pos;
        }
        if (new_white_pos != white_pos) {
            auto column = scaled.get_column(white_pos);
            fl_draw_image_mono(column.data(), white_pos, window->h()-50, 1, 50);
            fl_line(new_white_pos, window->h(), new_white_pos, window->h() - 50);
            white_pos = new_white_pos;
        }
    }
}

int HistogramDisplay::handle(int event) {
    if (event == FL_PUSH and Fl::event_button() == FL_LEFT_MOUSE) {
        if (abs(Fl::event_x() - white_pos) < 4) {
            clicked = WHITE;
            return 1;
        }
        else if (abs(Fl::event_x() - black_pos) < 4) {
            clicked = BLACK;
            return 1;
        }
    }
    else if (event == FL_DRAG) {
        if (clicked == WHITE) {
            new_white_pos = Fl::event_x();
            redraw();
        }
        else if (clicked == BLACK) {
            new_black_pos = Fl::event_x();
            redraw();
        }
        return 1;
    }
    else if (event == FL_RELEASE) {
        if (clicked == BLACK) {
            black_slider = (double)black_pos * (double)histogram.width()/(double)scaled.width();
            imagedisplay -> set_black(histogram_to_value[(int)black_slider]);
        }
        else if (clicked == WHITE) {
            white_slider = (double)white_pos * (double)histogram.width()/(double)scaled.width();
            imagedisplay -> set_white(histogram_to_value[(int)white_slider]);
        }
        clicked = NONE;
        return 1;
    }
    return 0;
}

HistogramDisplay::~HistogramDisplay() {

}
