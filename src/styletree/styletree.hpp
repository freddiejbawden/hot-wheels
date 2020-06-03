#pragma once
#ifndef STYLETREE
#define STYLETREE

#include <unordered_map>
#include "../css/cssnodes/values/value.hpp"
#include "../domnodes/node.hpp"
#include "../css/cssnodes/rule.hpp"
#include "../css/cssnodes/declaration.hpp"
#include "displayType.hpp"
#include "../css/cssnodes/selectors/simple_selector.hpp"

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
    DisplayType getDisplayType();
};

#endif