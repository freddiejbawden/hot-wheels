#pragma once
#ifndef CSS_KEYWORD
#define CSS_KEYWORD
#include <string>
#include "value.hpp"
class Keyword : public Value {
  public:
    std::string value;
    void display();
    float toPX();
};

#endif
