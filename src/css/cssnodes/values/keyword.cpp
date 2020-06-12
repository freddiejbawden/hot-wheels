#include "keyword.hpp"
#include <iostream>

void Keyword::display() {
  std::cout << value;
}

int Keyword::toPX() {
  if (value == "auto") {
    return 0;
  } else {
    return 0;
  }
}