#pragma once
#ifndef CSS_LENGTH
#define CSS_LENGTH
#include "value.hpp"
#include "units.hpp"
#include <string>
class Length : public Value {
  public:
    int value;
    Unit unit;
   Length(int value);

    Length(std::string str_value);
    Length() = default;
    void display();
    int toPX();
};
#endif