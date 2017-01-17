#include "ReversibleImage.h"

ReversibleImage::ReversibleImage(uchar* data, int width, int height) {
    CImg::CImg(data, width, height);
}


void ReversibleImage::draw_image(CImg<uchar>& new_image) {
    auto min_height = std::min(height(), new_image.height());
    auto min_width = std::min(width(), new_image.width());

    for (auto y = 0; y < min_height; y++) {
        for (auto x = 0; x < min_width; x++) {
            if (this->(x, y) != new_image(x, y) or x >= width() or y >= height()) {
                changed.push_back({x, y, new_image(x, y)});
            }
        }
    }
}


void ReversibleImage::flush(int x0, int y0) {
    std::stable_sort(changed.begin(), changed.end());

    for (auto const& px : changed) {
        fl_color(px.color, px.color, px.color);
        fl_point(px.x + x0, px.y + y0);
    }
}


void ReverseibleImage::revert(int x0, int y0) {
    for (auto& px : changed) {
        px.color = this->(px.x, px.y);
    }

    std::stable_sort(changed.begin(), changed.end());

    for (auto const& px : changed) {
        fl_color(px.color, px.color, px.color);
        fl_point(px.x + x0, px.y + y0);
    }
}