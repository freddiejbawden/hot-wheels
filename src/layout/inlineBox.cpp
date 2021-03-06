#include "layout/inlineBox.hpp"
#include "domnodes/text.hpp"
#include "domnodes/element.hpp"
#include "cssnodes/values/keyword.hpp"
#include "fontmanager/fontmanager.hpp"
#include "utils/utils.hpp"

InlineBox::InlineBox(StyledNode* node) : LayoutBox(node) {};

void InlineBox::displayBoxType() {
  std::cout << "box: inline ";
}
void InlineBox::calculateWidth(Dimensions parent) {
  Keyword* autoWidth = new Keyword();
  autoWidth->value = "auto";
  Value* margin_left  = node->getPropertyValueOrDefault("margin-left", "margin", autoWidth);
  Value* margin_right = node->getPropertyValueOrDefault("margin-right", "margin", autoWidth);

  Value* border_left  = node->getPropertyValueOrDefault("border-left-width", "border-width", autoWidth);
  Value* border_right = node->getPropertyValueOrDefault("border-right-width", "border-width", autoWidth);

  Value* padding_left  = node->getPropertyValueOrDefault("padding-left", "padding", autoWidth);
  Value* padding_right = node->getPropertyValueOrDefault("padding-right", "padding", autoWidth);
  
  dimensions.border.left = border_left->toPX();
  dimensions.border.right = border_right->toPX();
  dimensions.margin.left = margin_left->toPX();
  dimensions.margin.right = margin_right->toPX();
  dimensions.padding.left = padding_left->toPX();
  dimensions.padding.right = padding_right->toPX();

  if (typeid(*(node->node)) == typeid(Text)) {
    Text* t = (Text*) node->node;
    FontManager *fm  = FontManager::getInstance();

    Value* fontsize = node->getPropertyValue("font-size");
    int w = fm->getWidthOfText("arial",node->parent->getPropertyValue("font-size")->toPX(), t->text);
    if (w > parent.content.width) {
      dimensions.content.width = parent.content.width;
    } else {
      dimensions.content.width = w;
    }

  } else {
    // else fill all available space
    dimensions.content.width = parent.content.width;
  }
  
};
void InlineBox::calculatePosition(Dimensions parent) {
  dimensions.content.x = parent.content.x + dimensions.margin.left + dimensions.padding.left;
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
    dimensions.content.width = sum;
  }
};
void InlineBox::calculateHeight() {
    if (typeid(*(node->node)) == typeid(Text)) {
      Text* t = (Text*) node->node;
      FontManager *fm  = FontManager::getInstance();
      int fontsize = node->parent->getPropertyValue("font-size")->toPX();
      
      std::vector<std::string> out;
      size_t pos = 0;
      // make this a util function
      std::string token;
      std::string text = t->text;
      utils::splitString(text, &out);    
      int currentWidth = 0;
      
      int h = 0;
      int textsize = fm->getHeightOfText("arial", fontsize, t->text);
      for (std::vector<std::string>::iterator it = out.begin(); it != out.end(); ++it) {
        std::string s = *it;
        int wordWidth = fm->getWidthOfText("arial", fontsize, s);
        if (currentWidth + wordWidth > dimensions.content.width) {
          h += textsize;
          currentWidth = wordWidth;
        } else {
          currentWidth += wordWidth;
        }
      };
      h += textsize;
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


