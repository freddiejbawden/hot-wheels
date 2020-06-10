
#include "anonymousBox.hpp"
#include <iostream>

void AnonymousBox::displayBoxType() {
  std::cout << "box: anon ";
}

AnonymousBox::AnonymousBox() { node = NULL; }
void AnonymousBox::calculateWidth(Dimensions parent) {
  dimensions = parent;
};
void AnonymousBox::calculatePosition(Dimensions parent) {
  dimensions = parent;
  dimensions.content.y = parent.content.y + parent.content.height;
};
void AnonymousBox::calculateChildren() {
  Dimensions lineBox = dimensions;
  int xBound = lineBox.content.x + lineBox.content.width;
  bool first = true;
  for (std::vector<LayoutBox*>::iterator it = children.begin(); it != children.end(); ++it) {
    LayoutBox* child = (*it);
    // Maybe handle split in this function? return a split child?
    child->createLayout(lineBox);
    Dimensions childDims = child->dimensions;
    if (first) {
      first = false;
      lineBox.content.height = childDims.content.height;
    }
    if(lineBox.content.x + childDims.content.width > xBound)  {
      std::cout << xBound << " " << (lineBox.content.x + childDims.content.width) << "\n" ;
      // handle split and make a new line box
      // TODO: account for padding
      lineBox.content.y += childDims.content.height;
      lineBox.content.x = dimensions.content.x;
      dimensions.content.height += childDims.content.height;
      // doing this twice is ineffcient, we will probably need to 
      // make createLayout(..) an interface 
      child->createLayout(lineBox);
    } else {
      // there is space to spare
      lineBox.content.x += childDims.content.width;
    }
  }
  dimensions.content.height = lineBox.content.height;
};
void AnonymousBox::calculateHeight() {

};


