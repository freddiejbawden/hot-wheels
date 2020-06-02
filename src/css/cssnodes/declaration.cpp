#include "declaration.hpp"
#include <iostream>
void Declaration::display() {
  std::cout << name << ": \"";
  value->display();
  std::cout << '"';
}