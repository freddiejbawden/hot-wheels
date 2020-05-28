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