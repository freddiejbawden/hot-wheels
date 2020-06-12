
#include "lineBox.hpp"
#include <iostream>

void LineBox::displayBoxType() {
  std::cout << "box: line";
}

LineBox::LineBox() { node = NULL; }
void LineBox::calculateWidth(Dimensions parent) {
  dimensions = parent;
};
void LineBox::calculatePosition(Dimensions parent) {
  dimensions = parent;
};
void LineBox::calculateChildren() {
  for (std::vector<LayoutBox*>::iterator it = children.begin(); it != children.end(); ++it) {
    LayoutBox* child = (*it);
    child->createLayout(dimensions);
  }
};
void LineBox::calculateHeight() {
  
};


