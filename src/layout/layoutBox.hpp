#pragma once
#ifndef LAYOUT_BOX
#define LAYOUT_BOX

#include "boxType.hpp"
#include "../styletree/styletree.hpp"

typedef struct Rect {
    float x;
    float y;
    float width;
    float height;
} Rect;

typedef struct EdgeSizes {
    float left;
    float right;
    float top;
    float bottom;
} EdgeSizes;

typedef struct Dimensions {
    Rect content;

    // Surrounding edges:
    EdgeSizes padding;
    EdgeSizes border;
    EdgeSizes margin;
} Dimensions;

class LayoutBox {
  public:
    Dimensions dimensions;
    BoxType box_type;
    StyledNode* node;
    std::vector<LayoutBox*> children;
    void display(int level);
    void displayChildren(int level);

    LayoutBox(StyledNode* node);
    LayoutBox();
    void setBoxType();
    LayoutBox* createAnonymousInlineBox();

};


#endif