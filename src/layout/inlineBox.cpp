
#include "inlineBox.hpp"
#include "../domnodes/text.hpp"
InlineBox::InlineBox(StyledNode* node) : LayoutBox(node) {};
void InlineBox::calculateWidth(Dimensions parent) {
 // shrink to fit, calculate the preffered width
  
};
void InlineBox::calculatePosition(Dimensions parent) {};
void InlineBox::calculateChildren() {};
void InlineBox::calculateHeight() {};


