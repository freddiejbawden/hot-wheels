#include <algorithm>


#include "layout/blockBox.hpp"
#include "cssnodes/values/length.hpp"
#include "cssnodes/values/keyword.hpp"
#include "domnodes/element.hpp"
#include "fontmanager/fontmanager.hpp"

BlockBox::BlockBox(StyledNode* node) : LayoutBox(node) {};

void BlockBox::displayBoxType() {
  std::cout << "box: block ";
}

void BlockBox::calculateWidth(Dimensions parent) {
    
  // make lengtth constructor that takes values
  Keyword* autoWidth = new Keyword();
  autoWidth->value = "auto";
  Value* width      = node->getPropertyValueOrDefault("width", autoWidth);

  Value* margin_left  = node->getPropertyValueOrDefault("margin-left", "margin", autoWidth);
  Value* margin_right = node->getPropertyValueOrDefault("margin-right", "margin", autoWidth);

  Value* border_left  = node->getPropertyValueOrDefault("border-left-width", "border-width", autoWidth);
  Value* border_right = node->getPropertyValueOrDefault("border-right-width", "border-width", autoWidth);

  Value* padding_left  = node->getPropertyValueOrDefault("padding-left", "padding", autoWidth);
  Value* padding_right = node->getPropertyValueOrDefault("padding-right", "padding", autoWidth);
  std::vector<Value*> widths = std::vector<Value*>{width, margin_left, margin_right, border_left, border_right, padding_left, padding_right};
  // the total must be equal to the width of the containing block
  int total = 0;
  for (std::vector<Value*>::iterator it = widths.begin(); it != widths.end(); ++it) {
    Value* v = *it;
    total += v->toPX();
  }
  // Based on the condittions https://www.w3.org/TR/CSS2/visudet.html#blockwidth
  
  /* Condition 1: If 'width' is not 'auto' and 'border-left-width' + 'padding-left' + 'width' + 
  'padding-right' + 'border-right-width' (plus any of 'margin-left' or 'margin-right' that are not 
  'auto') is larger than the width of the containing block, then any 'auto' values for 'margin-left' 
  or 'margin-right' are, for the following rules, treated as zero. */
  if (width != autoWidth) {
    int cond1Sum =  border_left->toPX() + padding_left->toPX() + width->toPX() 
                      + padding_right->toPX() + border_right->toPX();

    if (margin_left   != autoWidth) cond1Sum += margin_left->toPX();
    if (margin_right  != autoWidth) cond1Sum += margin_right->toPX();
    if (cond1Sum > parent.content.width) {
      if (margin_left == autoWidth) {
        margin_left = new Length(0.0);
      }
      if (margin_right == autoWidth) {
        margin_right = new Length(0.0);
      }
    }
  } else {
    int underflow = parent.content.width - total;

    /*Condition 2: If all of the above have a computed value other than 'auto', the values are said 
    to be "over-constrained" and one of the used values will have to be different from its computed 
    value. If the 'direction' property of the containing block has the value 'ltr', the specified 
    value of 'margin-right' is ignored and the value is calculated so as to make the equality true. 
    If the value of 'direction' is 'rtl', this happens to 'margin-left' instead. */
    bool isOverconstrained = std::all_of(widths.begin(), widths.end(), [autoWidth](Value* v){return v == autoWidth; });
    if (isOverconstrained && total > parent.content.width) {
      if (((Keyword*) node->getPropertyValue("direction"))->value == "rtl") {
        margin_left = new Length(underflow);
      } else {
        margin_right = new Length(underflow);
      }
    }

    /*Condition 3: If there is exactly one value specified as 'auto', its used value follows from the 
      equality */ 
    Value* single = NULL;
    for (std::vector<Value*>::iterator it = widths.begin(); it != widths.end(); ++it) {
      if ((*it) == autoWidth) {
        if (single == NULL) {
          single = (*it);
        } else {
          single = NULL;
          break;
        }
      }
    }
    if (single != NULL) {
      single = new Length(underflow);
    }

    /* Condition 4: If 'width' is set to 'auto', any other 'auto' values become '0' and 'width' 
      follows from the resulting equality. */
    if (width == autoWidth) {
      // width is the first element
      for (std::vector<Value*>::iterator it = widths.begin() + 1; it != widths.end(); ++it) {
        if (*it == autoWidth) {
          (*it) = new Length(0.0);
        }
      }
      if (underflow >= 0.0) {
        width = new Length(underflow);
      } else {
        width = new Length(0.0);
        margin_right = new Length(margin_right->toPX() + underflow);
      }
    } else {
      if (margin_left == autoWidth && margin_right == autoWidth) {
        margin_left = new Length(underflow / 2.0);
        margin_right = new Length(underflow / 2.0);
      }
    }
  }

  
  
  dimensions.border.left = border_left->toPX();
  dimensions.border.right = border_right->toPX();
  dimensions.margin.left = margin_left->toPX();
  dimensions.margin.right = margin_right->toPX();
  dimensions.padding.left = padding_left->toPX();
  dimensions.padding.right = padding_right->toPX();
  dimensions.content.width = width->toPX();

}

void BlockBox::calculatePosition(Dimensions parent) {
  Length* zero = new Length(0.0);
  dimensions.margin.top = node->getPropertyValueOrDefault("margin-top", "margin", zero)->toPX();
  dimensions.margin.bottom = node->getPropertyValueOrDefault("margin-bottom", "margin", zero)->toPX();

  dimensions.border.top = node->getPropertyValueOrDefault("border-top-width", "border-width", zero)->toPX();
  dimensions.border.bottom = node->getPropertyValueOrDefault("border-bottom-width", "border-width", zero)->toPX();

  dimensions.padding.top = node->getPropertyValueOrDefault("padding-top", "padding", zero)->toPX();
  dimensions.padding.bottom = node->getPropertyValueOrDefault("padding-bottom", "padding", zero)->toPX();
  dimensions.content.x = parent.content.x + dimensions.margin.left + dimensions.border.left + dimensions.padding.left;
  dimensions.content.y = parent.content.height +  parent.content.y + dimensions.margin.top + dimensions.border.top + dimensions.padding.top;
}
void BlockBox::calculateChildren() {
  for (std::vector<LayoutBox*>::iterator it = children.begin(); it != children.end(); ++it) {
    LayoutBox* child = (*it);
    child->createLayout(dimensions);
    dimensions.content.height += child->dimensions.marginBox()->height;
  }
}
void BlockBox::calculateHeight() {
  // check if there is a css property that mandates height, if so override the height
  // calculated in BlockBox::calculateChildren
  Value* height = node->getPropertyValue("height");
  if (height != NULL) {
    dimensions.content.height = height->toPX();
  }
  // Add a new line each 
  if (typeid(*(node->node)) == typeid(Element)) {
      Element* e = (Element*) node->node;
      if (e->tag_name == "p") {
        dimensions.padding.bottom +=  FontManager::DEFAULT_TEXTSIZE;
      }
  }
}