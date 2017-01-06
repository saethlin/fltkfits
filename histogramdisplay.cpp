#include "histogramdisplay.h"
#include <iostream>
#include <math.h>


HistogramDisplay::HistogramDisplay(CImg<double>& image, Fl_Window* window, ImageDisplay* imagedisplay) : Fl_Box(0, window->h()-50, window->w()-200, 50) {
    this->window = window;
    this->imagedisplay = imagedisplay;

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
}

void HistogramDisplay::draw() {
    if (window->w()-200 != scaled.width()) {
        scaled = histogram.get_resize(window->w()-200, 50, 1, 1, 1);
    }
    fl_draw_image_mono(scaled.data(), 0, window->h()-50, scaled.width(), scaled.height()+1);

    int black_pos = black_slider * scaled.width()/histogram.width();
    int white_pos = white_slider * scaled.width()/histogram.width();

    fl_color(255, 0, 0);
    fl_line(black_pos, window->h(), black_pos, window->h()-50);
    fl_line(white_pos, window->h(), white_pos, window->h()-50);
}

int HistogramDisplay::handle(int event) {
    return 1;
}