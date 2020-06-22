
#include "layout/anonymousBox.hpp"
#include <iostream>

void AnonymousBox::displayBoxType() {
  std::cout << "box: anon ";
}

AnonymousBox::AnonymousBox() { node = NULL; }
void AnonymousBox::calculateWidth(Dimensions parent) {
  dimensions.content.width = parent.content.width;
};
void AnonymousBox::calculatePosition(Dimensions parent) {
  dimensions.content.x = parent.content.x;
  dimensions.content.y = parent.content.y;
};
void AnonymousBox::calculateChildren() {
  Dimensions lineBox = dimensions;
  int xBound = lineBox.content.x + lineBox.content.width;
  bool wrapped = true;
  for (std::vector<LayoutBox*>::iterator it = children.begin(); it != children.end(); ++it) {
    LayoutBox* child = (*it);
    // Maybe handle split in this function? return a split child?
    child->createLayout(lineBox);
    Dimensions childDims = child->dimensions;
    if(lineBox.content.x + childDims.content.width > xBound)  {
      std::cout << "recalculating " << childDims.content.height << '\n';
      // handle split and make a new line box
      // TODO: account for padding
      lineBox.content.x = dimensions.content.x;
      lineBox.content.y = dimensions.content.height + dimensions.content.y;
      wrapped = true;
      std::cout << dimensions.content.height << " new height \n";
      // doing this twice is ineffcient, we will probably need to 
      // make createLayout(..) an interface 
      child->createLayout(lineBox);

    }
    lineBox.content.x += childDims.content.width;
    if (wrapped) {
      dimensions.content.height += childDims.content.height;
      wrapped = false;
    }
  }
};
void AnonymousBox::calculateHeight() {

};


