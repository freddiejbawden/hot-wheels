#pragma once
#ifndef CSS_RULE
#define CSS_RULE
#include <vector>
#include "selectors/selector.hpp"
#include "declaration.hpp"

class Rule {
  public:
    std::vector<Selector* > selectors;
    std::vector<Declaration> declarations;
    void display();
};
#endif 