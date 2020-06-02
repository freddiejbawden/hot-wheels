#include <iostream>
#include "styletree.hpp"
#include "../domnodes/text.hpp"
#include "../domnodes/element.hpp"


void StyledNode::display() {
  if (typeid(*node) == typeid(Element)) {
    Element *e = (Element*) node;
    std::cout << e->tag_name << " {";
    for(auto& prop: properties) {
      std::cout << prop.first << ": " << prop.second << " ";
    }
  }
  std::cout << "}\n";
  for (std::vector<StyledNode*>::iterator it = children.begin(); it != children.end(); ++it) {
    (*it)->display();
  }

}
// This whole thing needs tidied, bad polymorphism i think
StyledNode::StyledNode(Node* domNodeRoot, std::vector<Rule*> styleRules) {
  node = domNodeRoot;
  // we can't style text nodes so return
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