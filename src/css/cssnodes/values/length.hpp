#pragma once
#ifndef CSS_LENGTH
#define CSS_LENGTH
#include "value.hpp"
#include "units.hpp"

class Length : public Value {
  public:
    float value;
    Unit unit;
};
#endif