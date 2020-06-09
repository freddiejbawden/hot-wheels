#pragma once
#ifndef INLINE_BOX
#define INLINE_BOX
#include "layoutBox.hpp"

class InlineBox : public LayoutBox {
  public:
    InlineBox(StyledNode* node);
    void calculateWidth(Dimensions parent);
    void calculatePosition(Dimensions parent);
    void calculateChildren();
    void calculateHeight();
};

#endif