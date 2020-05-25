#include "element.hpp"

void Element::displayAttributes() {
  std::cout << "[Attributes: "; 
  for (auto& elm: attributes) {
    std::cout << elm.first << ":" << elm.second << " ";
  }
    std::cout << "] "; 

}

void Element::display() {
    std::cout << "(Element " << tag_name;
    displayAttributes(); 
    displayChildren();
    std::cout << ")\n";
}

void Element::addAttribute(std::string attribute_name, std::string attribute_value) {
  attributes[attribute_name] = attribute_value;
}

Element::Element(std::string tn) {
  tag_name = tn;
}