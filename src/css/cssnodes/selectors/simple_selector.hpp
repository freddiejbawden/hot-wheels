#pragma once
#ifndef CSS_SIMPLE_SELECTOR
#define CSS_SIMPLE_SELECTOR

#include <string>
#include <vector>
#include "selector.hpp"
class SimpleSelector : public Selector {
  public:
    std::string tag_name;
    std::string id;
    std::vector<std::string> classes;
    bool is_universal;
    SimpleSelector() = default;
};
#endif