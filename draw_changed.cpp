#include "draw_changed.h"

bool pixel_compare(const pixel& lhs, const pixel& rhs) {
    return lhs.color < rhs.color;
}

void draw_changed(CImg<uchar>& old, CImg<uchar>& fresh, int x0, int y0, int width, int height) {
    auto changed = std::vector<pixel>();

    for (auto y = 0; y < height; y++) {
        for (auto x = 0; x < width; x++) {
            if (x >= old.width() or y >= old.height() or old(x, y) != fresh(x, y)) {
                changed.push_back({x + x0, y + y0, fresh(x, y)});
            }
        }
    }

    std::stable_sort(changed.begin(), changed.end(), pixel_compare);

    if (changed.size() != 0) {
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
