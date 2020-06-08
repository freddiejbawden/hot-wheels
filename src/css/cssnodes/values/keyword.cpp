#include "keyword.hpp"
#include <iostream>

void Keyword::display() {
  std::cout << value;
}

float Keyword::toPX() {
  if (value == "auto") {
    return 0;
  } else {
    return 0;
  }
}