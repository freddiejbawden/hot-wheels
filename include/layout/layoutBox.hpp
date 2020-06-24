#pragma once
#ifndef LAYOUT_BOX
#define LAYOUT_BOX

#include "dimensions.hpp"
#include "../styletree/styletree.hpp"

class LayoutBox {
  public:
    Dimensions dimensions;
    StyledNode* node;
    std::vector<LayoutBox*> children;
    Dimensions* getDimensions();
    void display(int level);
    void displayChildren(int level);

    LayoutBox(StyledNode* node);
    LayoutBox() = default;
    void setBoxType();
    LayoutBox* createAnonymousInlineBox();
    void createLayout(Dimensions parent);
    virtual void calculateWidth(Dimensions parent);
    virtual void calculatePosition(Dimensions parent);
    virtual void calculateChildren();
    virtual void calculateHeight();
    virtual void displayBoxType();

};


#endif