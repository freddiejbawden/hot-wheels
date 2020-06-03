#include "layoutBox.hpp"
#include "boxType.hpp"
#include "../domnodes/element.hpp"
#include "../domnodes/text.hpp"

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

