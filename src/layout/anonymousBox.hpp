#pragma once
#ifndef ANONYMOUS_BOX
#define ANONYMOUS_BOX
#include "layoutBox.hpp"

class AnonymousBox : public LayoutBox {
  public:
    AnonymousBox();
        void calculateWidth(Dimensions parent);
    void calculatePosition(Dimensions parent);
    void calculateChildren();
    void calculateHeight();
    void displayBoxType();
};
#endif 