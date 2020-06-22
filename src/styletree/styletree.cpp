#include <iostream>
#include "styletree/styletree.hpp"
#include "domnodes/text.hpp"
#include "domnodes/element.hpp"
#include "cssnodes/values/keyword.hpp"
#include "cssnodes/values/length.hpp"
#include "fontmanager/fontmanager.hpp"

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
Value* StyledNode::getPropertyValueOrDefault(std::string property1,std::string property2, Value* d) {
  if (properties.count(property1) == 0) {
    if (properties.count(property2) == 0) {
      return d;
    } else {
      return properties[property2];
    }
  } else {
    return properties[property1];
  }
}


Value* StyledNode::getPropertyValueOrDefault(std::string property, Value* d) {
  if (properties.count(property) == 0) {
    return d;
  }
  return properties[property];
}

Value* StyledNode::getPropertyValue(std::string property) {
  if (properties.count(property) == 0) {
    return NULL;
  }
  return properties[property];
}

DisplayType StyledNode::getDefaultDisplayType() {
  // switch to an external list
  if (typeid(*node) == typeid(Element)) {
    Element *elm = (Element*) node;
    std::string tag = elm->tag_name;
    if (tag == "span") {
      return DisplayType::Inline;
    }
  }
  return DisplayType::Block;
}

DisplayType StyledNode::getDisplayType() {
  if (typeid(*node) == typeid(Text)) {
    return DisplayType::Inline;
  }
  Value* value = getPropertyValue("display");
  if (value == NULL) {
    return getDefaultDisplayType();
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

void StyledNode::setDefaults() {
  // make the defaults a static class
  if (typeid(*node) == typeid(Element)) {
    Element* e = (Element*) node;
    // this gets a hmm, probably a better way to do this
    std::cout << e->tag_name << '\n';
    if (e->tag_name == "h1") {
      properties["font-size"] = new Length(FontManager::DEFAULT_TEXTSIZE * 2);
    } else if (e->tag_name == "h2") {
      properties["font-size"] = new Length(FontManager::DEFAULT_TEXTSIZE * 1.5);
    } else if (e->tag_name == "h3") {
      properties["font-size"] = new Length(FontManager::DEFAULT_TEXTSIZE * 1.17);
    } else if (e->tag_name == "h4") {
      properties["font-size"] = new Length(FontManager::DEFAULT_TEXTSIZE * 1);
    } else if (e->tag_name == "h5") {
      properties["font-size"] = new Length(FontManager::DEFAULT_TEXTSIZE * 0.83);
    } else if (e->tag_name == "h6") {
      properties["font-size"] = new Length(FontManager::DEFAULT_TEXTSIZE * 0.67);
    } else {
      properties["font-size"] = new Length(FontManager::DEFAULT_TEXTSIZE);
    }
  }
}
// This whole thing needs tidied, bad polymorphism i think
StyledNode::StyledNode(Node* domNodeRoot, std::vector<Rule*> styleRules, StyledNode* _parent) {
  node = domNodeRoot;
  parent = _parent;

  if (typeid(*domNodeRoot) == typeid(Text)) {
    return;
  };
  properties = std::unordered_map<std::string, Value*>();
  if (parent != nullptr) {
    // some properties are inherited, like font-size - we should make a const with all of them and 
    // loop through? 
    properties["font-size"] = parent->getPropertyValueOrDefault("font-size", new Length(16));
  }
  setDefaults();
  Element*  elm = (Element*) node;
  // check for widtth and height attributes and add to styling
  if (elm->getAttribute("width") != "") {
    std::string attrWidth = elm->getAttribute("width");
    properties["width"] = new Length(attrWidth);
  }
  if (elm->getAttribute("height") != "") {
    std::string attrWidth = elm->getAttribute("height");
    properties["height"] = new Length(attrWidth);
  }
  
  children = std::vector<StyledNode*>();
  match(styleRules);
 
  // recurse to children
  for (std::vector<Node*>::iterator it = domNodeRoot->children.begin(); it != domNodeRoot->children.end(); ++it) {
    children.push_back(new StyledNode(*it, styleRules, this));
  }
}    
StyledNode::StyledNode(Node* domNodeRoot, std::vector<Rule*> styleRules) : StyledNode(domNodeRoot, styleRules, nullptr) {};

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