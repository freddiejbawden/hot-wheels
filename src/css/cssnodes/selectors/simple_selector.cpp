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
  std::cout << " | Spec (";
  std::vector<int> sp = getSpecificity();
  std::cout << sp[0] << " ";
  std::cout << sp[1] << " ";
  std::cout << sp[2] << " ";
  std::cout << "))";

 }

 std::vector<int> SimpleSelector::getSpecificity() {
    std::vector<int>  specificity = std::vector<int>{0,0,0};
    if (id != "") {
      specificity[0] = 1;
    }
    specificity[1] = classes.size();
    if (tag_name != "") {
      specificity[2] = 1;
    }
    return specificity;
 }