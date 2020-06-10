#pragma once
#ifndef LAYOUT_RECT
#define LAYOUT_RECT

#include "edgeSizes.hpp"

class Rect {
  public:
    int x;
    int y;
    int width;
    int height;
    Rect* expandedBy(EdgeSizes edge);
    Rect() = default;
};

#endif