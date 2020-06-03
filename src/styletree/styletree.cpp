#include <iostream>
#include "styletree.hpp"
#include "../domnodes/text.hpp"
#include "../domnodes/element.hpp"
#include "../css/cssnodes/values/keyword.hpp"

void StyledNode::display(int level) {
  if (typeid(*node) == typeid(Element)) {
    Element *e = (Element*) node;
    std::cout << e->tag_name << " [";
    switch (getDisplayType()) 
    {
    case DisplayType::Block:
      std::cout << "display: block] ";
      break;
    case DisplayType::Inline:
      std::cout << "display: inline] ";
      break;
    case DisplayType::None:
      std::cout << "display: none] ";
      break;
    default:
      std::cout << "display: unknown] ";
      break;
    }
    if (properties.bucket_count() > 0) {
      std::cout << " {";
      size_t j = 0;
      for(auto& prop: properties) {
        std::cout << prop.first << ": ";
        Value* v = prop.second;
        v->display();
        if (j < properties.bucket_count() - 1) {
          std::cout << ", ";
        }
        j++;
      }
      std::cout << "}";
    }
  } else if (typeid(*node) == typeid(Text)) {
    Text *t = (Text*) node;
    std::cout << '"' << t->text << '"';
  }
  displayChildren(level);
}

void StyledNode::displayChildren(int level) {
  std::cout << "\n";
  for (std::vector<StyledNode* >::size_type i = 0; i != children.size(); i++) {
     std::cout << std::string(level, '\t');
     if (i == children.size() - 1) {
      std::cout << "└── ";
    } else {
      std::cout << "├── ";
    }
    children[i]->display(level + 1);
    if (i != children.size() - 1) {
    }
  }
}

Value* StyledNode::getPropertyValue(std::string property) {
  if (properties.count(property) == 0) {
    return NULL;
  }
  return properties[property];
}

DisplayType StyledNode::getDisplayType() {
  Value* value = getPropertyValue("display");
  if (value == NULL) {
    return DisplayType::Block;
  }
  Keyword *keywordValue = (Keyword*) value;
  if (keywordValue->value == "block") {
    return DisplayType::Block;
  } else if (keywordValue->value == "none") {
    return DisplayType::None;
  } else  {
    return DisplayType::Inline;
  }
}
// This whole thing needs tidied, bad polymorphism i think
StyledNode::StyledNode(Node* domNodeRoot, std::vector<Rule*> styleRules) {
  node = domNodeRoot;

  if (typeid(*domNodeRoot) == typeid(Text)) return;
  
  properties = std::unordered_map<std::string, Value*>();
  children = std::vector<StyledNode*>();
  match(styleRules);
  
  // recurse to children
  for (std::vector<Node*>::iterator it = domNodeRoot->children.begin(); it != domNodeRoot->children.end(); ++it) {
    children.push_back(new StyledNode(*it, styleRules));
  }
}    

void StyledNode::attatchDeclarations(std::vector<Declaration> d) {
  for (std::vector<Declaration>::iterator it = d.begin(); it != d.end(); ++it) {
    properties[it->name] = it->value;
  }
}


// this could probably be optimsied using hashing and stuffs
void  StyledNode::match(std::vector<Rule*> rules) {
  for (std::vector<Rule*>::iterator it = rules.begin(); it != rules.end(); ++it) {
    Rule *r = *it;
    for (std::vector<Selector*>::iterator selectorIt = r->selectors.begin(); selectorIt != r->selectors.end(); ++selectorIt) {
      Selector* s = *selectorIt;
      if (typeid(*s) == typeid(SimpleSelector)) {
        if (matchSimpleSelector((SimpleSelector*) s)) {
         attatchDeclarations(r->declarations);
        }
      } else {
        std::cout << "Unknown Type";
      }
    }
  }
}

bool StyledNode::matchSimpleSelector(SimpleSelector* s) {
  Element* e = (Element*) node;
  
  // if the tag name in the selector does not match the element
  // the style does not match
  if (s->tag_name != "" && s->tag_name != e->tag_name) {
    return false;
  }

  if (s->id != "" && s->id != e->getId()) {
    return false;
  }
  // could be done with all/any

  // if a class that is in the selector is not in the element, there is not a match
  std::unordered_map<std::string, bool> classes = e->getClasses();
  for (std::vector<std::string>::iterator it = s->classes.begin(); it != s->classes.end(); ++it) {
   // check if the class is attributed to the element
   auto matchedClass = classes.find(*it);
   if (matchedClass == classes.end()) {
     return false;
   }
  }
  return true;
}