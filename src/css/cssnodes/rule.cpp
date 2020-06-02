#include <iostream>
#include "rule.hpp"

void Rule::display() {
  std::cout << "RULE:{Selectors=(";
  for (std::vector<Selector*>::iterator it = selectors.begin(); it != selectors.end(); ++it) {
    Selector* s = *it;
    s->display();
    std::cout << " ";
  }
  std::cout << "), Declarations=(";

  for (std::vector<Declaration>::iterator it = declarations.begin(); it != declarations.end(); ++it) {
    Declaration d = *it;
    d.display();
    std::cout << ", ";
  }
  std::cout << ")}\n";
}