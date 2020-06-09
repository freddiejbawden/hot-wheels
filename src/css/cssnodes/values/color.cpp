#include "color.hpp"
#include <iostream>

void Color::display(){
  printf("Color {%d %d %d %d}", r,g,b,a);
}

float Color::toPX() {
  std::cout << "Cannot convert color to PX!\n";
  return 0;
}