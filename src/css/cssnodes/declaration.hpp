#pragma once
#ifndef CSS_DECLARATION
#define CSS_DECLARATION
#include <string>
#include "values/value.hpp"

class Declaration {
  public:
    std::string name;
    Value *value;
};
#endif
