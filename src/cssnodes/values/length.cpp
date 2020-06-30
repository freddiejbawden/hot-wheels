#include "cssnodes/values/length.hpp"
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
  case percent:
  {
    unitSymbol = "%";
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

Length::Length(int v) {
  value = v;
  unit = Unit::px;
}

int Length::toPX() {
  if (unit == Unit::px) {
    return value;
  }  else if (unit == Unit::percent) {
    std::cout << "Trying to access PX value of percentage!\n";
    return 0;
  } else {
    return 0;
  }
}