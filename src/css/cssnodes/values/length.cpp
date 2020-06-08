#include "length.hpp"
#include <iostream>

void Length::display() {
  std::string unitSymbol = "invalid";
  switch (unit)
  {
  case px: 
  {
    unitSymbol = "px";
  }
  break;
  default:
    break;
  }
  std::cout << value << unitSymbol;
}
Length::Length(std::string str_value) {
  value = std::stof(str_value);
  unit = Unit::px;
}

Length::Length(float v) {
  value = v;
  unit = Unit::px;
}

float Length::toPX() {
  if (unit == Unit::px) {
    return value;
  } else {
    return 0;
  }
}