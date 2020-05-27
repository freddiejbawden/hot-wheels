#include <iostream>

#include "simple_selector.hpp"


void SimpleSelector::display() {
  std::cout << "(";
  std::cout << tag_name;
  if (id != "") {
    std::cout << " #" << id << " ";
  }
  for (std::vector<std::string>::iterator it = classes.begin(); it != classes.end(); ++it) {
    std::cout << "." <<  *it << ", ";
  }
  if (is_universal) {
    std::cout << "* ";
  }
  std::cout << ")";

 }