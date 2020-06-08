#pragma once
#ifndef BLOCK_BOX
#define BLOCK_BOX
#include "layoutBox.hpp"

class BlockBox : public LayoutBox {
  public:
    BlockBox(StyledNode* node);
    void calculateWidth(Dimensions parent);
    void calculatePosition(Dimensions parent);
    void calculateChildren();
    void calculateHeight();

};

#endif