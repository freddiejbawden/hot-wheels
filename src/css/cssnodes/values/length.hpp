#pragma once
#ifndef CSS_LENGTH
#define CSS_LENGTH
#include "value.hpp"
#include "units.hpp"
#include <string>
class Length : public Value {
  public:
    float value;
    Unit unit;
   Length(float value);

    Length(std::string str_value);
    Length() = default;
    void display();
    float toPX();
};
#endif