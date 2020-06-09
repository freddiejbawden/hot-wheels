#include <algorithm>

#include "layoutBox.hpp"
#include "boxType.hpp"
#include "../domnodes/element.hpp"
#include "../domnodes/text.hpp"
#include "../css/cssnodes/values/length.hpp"
#include "../css/cssnodes/values/keyword.hpp"
#include "blockBox.hpp"
#include "inlineBox.hpp"
#include "anonymousBox.hpp"

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
  if (typeid(*this) == typeid(BlockBox)) {
    std::cout << "box: block] ";
  } else if (typeid(*this) == typeid(InlineBox)) {
    std::cout << "box: inline] ";
  } else if (typeid(*this) == typeid(AnonymousBox)) {
    std::cout << "box: anonymous] ";
  } else {
    std::cout << "WTF";
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


LayoutBox* LayoutBox::createAnonymousInlineBox() {
  
  if (node->getDisplayType() == DisplayType::Inline) {
    return this;
  } else if (node->getDisplayType() == DisplayType::Block) {
    if (children.size() > 0) {
      LayoutBox* last = children.back();
      if (typeid(*last) != typeid(AnonymousBox)) {
        children.push_back(new AnonymousBox());
      }
    } else {
      children.push_back(new AnonymousBox());
    }
    return children.back();
  } else if (typeid(*this) == typeid(AnonymousBox)) {
    return this;
  } else {
    Element *elm = (Element*) node->node;
    std::cout << "Error when creating anonymous box for tag: " << elm->tag_name << "\n"; 
    return this;
  }
}

LayoutBox::LayoutBox() {
  node = NULL;
}



void LayoutBox::calculateWidth(Dimensions d) {
  return;
} 

void LayoutBox::calculatePosition(Dimensions parent) {
  return;
}

void LayoutBox::calculateChildren() {
  for (std::vector<LayoutBox*>::iterator it = children.begin(); it != children.end(); ++it) {
    LayoutBox* child = (*it);
    child->createLayout(dimensions);
  }
}

void LayoutBox::calculateHeight() {
  return;
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

  for (std::vector<StyledNode*>::iterator it = node->children.begin(); it != node->children.end(); ++it) {
    StyledNode* child = (*it);
    switch(child->getDisplayType()) {
      case DisplayType::Block: 
        {
          children.push_back(new BlockBox(child));
        }
        break;
      case DisplayType::Inline:
        {
          // need to wrap in an inline container first
          createAnonymousInlineBox()->children.push_back(new InlineBox(child));
        } 
        break;
      case DisplayType::None:
      {
        // handle none
      }
    }
  }
}

