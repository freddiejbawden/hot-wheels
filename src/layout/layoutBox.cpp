#include <algorithm>

#include "layoutBox.hpp"
#include "boxType.hpp"
#include "../domnodes/element.hpp"
#include "../domnodes/text.hpp"
#include "../css/cssnodes/values/length.hpp"
#include "../css/cssnodes/values/keyword.hpp"

// this REALLY should be into an interface, this is just handling block display 
void LayoutBox::display(int level) {
  if (node == NULL) {
    std::cout << "[";
  } else {
    Node* domNode = node->node;
    if (typeid(*domNode) == typeid(Element)) {
      Element *e = (Element*) domNode;
      std::cout << e->tag_name << " [";   
    } else if (typeid(*domNode) == typeid(Text)) {
      Text *t = (Text*) domNode;
      std::cout << '"' << t->text << "\" [";
    } else {
      std::cout << "dom node not recognised!";
      exit(1); 
    }
  } 
  switch (box_type) 
  {
  case BoxType::BoxBlock:
    std::cout << "box: block] ";
    break;
  case BoxType::BoxInline:
    std::cout << "box: inline] ";
    break;
  case BoxType::BoxAnonymous:
    std::cout << "box: anonymous] ";
    break;
  default:
    std::cout << "Unknown box type!";
    exit(1);
    break;
  }
  displayChildren(level);
}

void LayoutBox::displayChildren(int level) {
  std::cout << "\n";
  for (std::vector<LayoutBox* >::size_type i = 0; i != children.size(); i++) {
     std::cout << std::string(level, '\t');
     if (i == children.size() - 1) {
      std::cout << "└── ";
    } else {
      std::cout << "├── ";
    }
    children[i]->display(level + 1);
  }
}
void LayoutBox::setBoxType() {
  switch (node->getDisplayType())
  {
  case DisplayType::Block: 
    {
        box_type = BoxType::BoxBlock;
    };
    break;
    case DisplayType::Inline: 
      {
        box_type = BoxType::BoxInline;
      } 
      break;
    case DisplayType::None: 
      {
        std::cout << "Root is display:none!"; exit(1); 
      } 
    break;
  default:
    {
      std::cout << "Root is display:none!"; exit(1); 
    }
    break;
  }
}

LayoutBox* LayoutBox::createAnonymousInlineBox() {
  switch(box_type) {
    case BoxType::BoxInline: 
      {
        return this;
      }
      break;
    case BoxType::BoxAnonymous: 
      {
        return this;
      }
      break;
    case BoxType::BoxBlock:
      {
        if (children.size() > 0) {
          LayoutBox* last = children.back();
          if (last->box_type != BoxType::BoxAnonymous) {
            children.push_back(new LayoutBox());
          }
        } else {
          children.push_back(new LayoutBox());
        }
        return children.back();

      }
      break;
    default:
      {
        std::cout << "BoxType unknown\n"; 
        exit(1);
      }
  }
  return this;
}

LayoutBox::LayoutBox() {
  box_type = BoxType::BoxAnonymous;
  node = NULL;
}



void LayoutBox::calculateWidth(Dimensions d) {
   
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
  float total = 0.0;
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
    float cond1Sum =  border_left->toPX() + padding_left->toPX() + width->toPX() 
                      + padding_right->toPX() + border_right->toPX();

    if (margin_left   != autoWidth) cond1Sum += margin_left->toPX();
    if (margin_right  != autoWidth) cond1Sum += margin_right->toPX();
    if (cond1Sum > d.content.width) {
      if (margin_left == autoWidth) {
        margin_left = new Length(0.0);
      }
      if (margin_right == autoWidth) {
        margin_right = new Length(0.0);
      }
    }
  }


  float underflow = d.content.width - total;

  /*Condition 2: If all of the above have a computed value other than 'auto', the values are said 
  to be "over-constrained" and one of the used values will have to be different from its computed 
  value. If the 'direction' property of the containing block has the value 'ltr', the specified 
  value of 'margin-right' is ignored and the value is calculated so as to make the equality true. 
  If the value of 'direction' is 'rtl', this happens to 'margin-left' instead. */
  bool isOverconstrained = std::all_of(widths.begin(), widths.end(), [autoWidth](Value* v){return v == autoWidth; });
  if (isOverconstrained && total > d.content.width) {
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
  
  dimensions.border.left = border_left->toPX();
  dimensions.border.right = border_right->toPX();
  dimensions.margin.left = margin_left->toPX();
  dimensions.margin.right = margin_right->toPX();
  dimensions.padding.left = padding_left->toPX();
  dimensions.padding.right = padding_right->toPX();
  dimensions.content.width = width->toPX();
} 

void LayoutBox::calculatePosition(Dimensions parent) {
  Length* zero = new Length(0.0);
  dimensions.margin.top = node->getPropertyValueOrDefault("margin-top", "margin", zero)->toPX();
  dimensions.margin.bottom = node->getPropertyValueOrDefault("margin-bottom", "margin", zero)->toPX();

  dimensions.border.top = node->getPropertyValueOrDefault("border-top-width", "border-width", zero)->toPX();
  dimensions.border.bottom = node->getPropertyValueOrDefault("border-bottom-width", "border-width", zero)->toPX();

  dimensions.padding.top = node->getPropertyValueOrDefault("padding-top", "padding", zero)->toPX();
  dimensions.padding.bottom = node->getPropertyValueOrDefault("padding-bottom", "padding", zero)->toPX();
  dimensions.content.x = parent.content.x + dimensions.margin.left + dimensions.border.left + dimensions.padding.left;
  dimensions.content.y = parent.content.y + dimensions.margin.top + dimensions.border.top + dimensions.padding.top;
}

void LayoutBox::calculateChildren() {
  for (std::vector<LayoutBox*>::iterator it = children.begin(); it != children.end(); ++it) {
    LayoutBox* child = (*it);
    child->createLayout(dimensions);
    dimensions.content.height = dimensions.content.height + child->dimensions.marginBox()->height;
  }
}

void LayoutBox::calculateHeight() {
  Value* height = node->getPropertyValue("height");
  if (height != NULL) {
    dimensions.content.height = height->toPX();
  }
}

void LayoutBox::createLayout(Dimensions d) {
  calculateWidth(d);
  calculatePosition(d);
  calculateChildren();
  calculateHeight();
}


LayoutBox::LayoutBox(StyledNode* root)
{
  node = root; 
  setBoxType();

  for (std::vector<StyledNode*>::iterator it = node->children.begin(); it != node->children.end(); ++it) {
    StyledNode* child = (*it);
    switch(child->getDisplayType()) {
      case DisplayType::Block: 
        {
          children.push_back(new LayoutBox(child));
        }
        break;
      case DisplayType::Inline:
        {
          // need to wrap in an inliine container first
          createAnonymousInlineBox()->children.push_back(new LayoutBox(child));
        } 
        break;
      case DisplayType::None:
      {
        // handle none
      }
    }
  }
}

