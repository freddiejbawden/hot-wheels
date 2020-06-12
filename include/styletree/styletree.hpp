#pragma once
#ifndef STYLETREE
#define STYLETREE

#include <unordered_map>
#include "cssnodes/values/value.hpp"
#include "domnodes/node.hpp"
#include "cssnodes/rule.hpp"
#include "cssnodes/declaration.hpp"
#include "displayType.hpp"
#include "cssnodes/selectors/simple_selector.hpp"

class StyledNode {
  public:
    Node* node;
    std::unordered_map<std::string, Value*> properties;
    std::vector<StyledNode*> children;
    StyledNode(Node* domNodeRoot, std::vector<Rule*> styleRules);
    void match(std::vector<Rule*> styleRules);
    bool matchSimpleSelector(SimpleSelector* s);
    void attatchDeclarations(std::vector<Declaration> d);
    void display(int level);
    void displayChildren(int level);
    Value* getPropertyValue(std::string property);
    Value* getPropertyValueOrDefault(std::string property, Value* d);
    Value* getPropertyValueOrDefault(std::string property1,std::string property2, Value* d);
    DisplayType getDefaultDisplayType();
    DisplayType getDisplayType();
};

#endif