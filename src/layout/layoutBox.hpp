#pragma once
#ifndef LAYOUT_BOX
#define LAYOUT_BOX

#include "dimensions.hpp"
#include "boxType.hpp"
#include "../styletree/styletree.hpp"

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
    void createLayout(Dimensions parent);
    void calculateWidth(Dimensions parent);
    void calculatePosition(Dimensions parent);
    void calculateChildren();
    void calculateHeight();

};


#endif