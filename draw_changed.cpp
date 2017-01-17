#include "draw_changed.h"

bool pixel_compare(const pixel& lhs, const pixel& rhs) {
    return lhs.color < rhs.color;
}

void draw_changed(CImg<uchar>& old, CImg<uchar>& fresh, int x0, int y0, int width, int height) {
    auto changed = std::vector<pixel>();

    for (auto y = 0; y < height; y++) {
        for (auto x = 0; x < width; x++) {
            if (old(x, y) != fresh(x, y) or x >= old.width() or y >= old.height()) {
                changed.push_back({x + x0, y + y0, fresh(x, y)});
            }
        }
    }

    std::stable_sort(changed.begin(), changed.end(), pixel_compare);

    for (auto const& px : changed) {
        fl_color(px.color, px.color, px.color);
        fl_point(px.x, px.y);
    }
}
