#include <iostream>
#include "nodes/element.hpp"
#include "nodes/text.hpp"

int main() {
  std::cout << "Hot wheels\n";
  Element root = Element("h1");
  root.addChild(new Text("hello node"));
  root.display();
}