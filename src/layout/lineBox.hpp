#pragma once
#ifndef LINE_BOX
#define LINE_BOX
#include "layoutBox.hpp"

class LineBox : public LayoutBox {
  public:
    LineBox();
        void calculateWidth(Dimensions parent);
    void calculatePosition(Dimensions parent);
    void calculateChildren();
    void calculateHeight();
    void displayBoxType();
};
#endif 