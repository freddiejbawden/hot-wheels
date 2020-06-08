#pragma once
#ifndef LAYOUT_RECT
#define LAYOUT_RECT

#include "edgeSizes.hpp"

class Rect {
  public:
    float x;
    float y;
    float width;
    float height;
    Rect* expandedBy(EdgeSizes edge);
    Rect() = default;
};

#endif