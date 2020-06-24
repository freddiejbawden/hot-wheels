#pragma once
#ifndef LAYOUT_RECT
#define LAYOUT_RECT

#include "edgeSizes.hpp"

class Rect {
  public:
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;
    Rect* expandedBy(EdgeSizes edge);
    Rect() = default;
};

#endif