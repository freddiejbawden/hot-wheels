#pragma once
#ifndef LAYOUT_DIMENSIONS
#define LAYOUT_DIMENSIONS
#include "rect.hpp"
#include "edgeSizes.hpp"

class Dimensions {
  public:
    Dimensions() = default;
    Rect content;
    
    // Surrounding edges:
    EdgeSizes padding;
    EdgeSizes border;
    EdgeSizes margin;
    Rect* paddingBox();
    Rect* borderBox();
    Rect* marginBox();

};

#endif