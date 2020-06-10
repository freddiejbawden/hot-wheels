
#include "inlineBox.hpp"

#include "../domnodes/text.hpp"
#include "../domnodes/element.hpp"
#include "fontmanager/fontmanager.hpp"

InlineBox::InlineBox(StyledNode* node) : LayoutBox(node) {};

void InlineBox::displayBoxType() {
  std::cout << "box: inline ";
}
void InlineBox::calculateWidth(Dimensions parent) {
  if (typeid(*(node->node)) == typeid(Text)) {
    Text* t = (Text*) node->node;
    FontManager *fm  = FontManager::getInstance();
    int w = fm->getWidthOfText("arial16", t->text);
    dimensions.content.width = w;

  } else {
    // else fill all available space
    dimensions.content.width = parent.content.width;
  }
};
void InlineBox::calculatePosition(Dimensions parent) {
  dimensions.content.x = parent.content.x;
  dimensions.content.y = parent.content.y;
};
void InlineBox::calculateChildren() {
  int sum = 0;
  for (std::vector<LayoutBox*>::iterator it = children.begin(); it != children.end(); ++it) {
    LayoutBox* child = (*it);
    child->createLayout(dimensions);
    sum += child->dimensions.content.width;
  }
  // Inline Elements shrink to fit children
  if (typeid(*(node->node)) == typeid(Element)) {
    std::cout << ((Element*) node->node)->tag_name << ": " << sum << "px\n";
    dimensions.content.width = sum;
  }
};
void InlineBox::calculateHeight() {
    if (typeid(*(node->node)) == typeid(Text)) {
      Text* t = (Text*) node->node;
      FontManager *fm  = FontManager::getInstance();
      int h = fm->getHeightOfText("arial16", t->text);
      dimensions.content.height = h;
    } else {
      int maxHeight = 0;
      for (std::vector<LayoutBox*>::iterator it = children.begin(); it != children.end(); ++it) {
        LayoutBox* child = (*it);
        if (child->dimensions.content.height > maxHeight) {
          maxHeight = child->dimensions.content.height;
        }
      }
      dimensions.content.height = maxHeight;
    }

};


