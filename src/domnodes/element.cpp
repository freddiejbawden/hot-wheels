#include "element.hpp"

void Element::displayAttributes() {
  std::cout << "[Attributes: "; 
  for (auto& elm: attributes) {
    std::cout << elm.first << "=\"" << elm.second << "\" ";
  }
    std::cout << "] "; 

}

void Element::display(int level) {
    std::cout << tag_name << " ";
    displayAttributes(); 
    displayChildren(level);
    if (level == 0) {
      std::cout << "\n";
    }
}

void Element::addAttribute(std::string attribute_name, std::string attribute_value) {
  attributes[attribute_name] = attribute_value;
}


std::string Element::getId() {
  auto id = attributes.find("id");
  if (id != attributes.end()) {
    return id->second;
  } else {    
    return "";
  }
}

 std::unordered_map<std::string, bool> Element::getClasses() {
  auto classes = attributes.find("class");
  std::unordered_map<std::string, bool> classMap;
  if (classes != attributes.end()) {
    std::string classString = classes->second;
    size_t i = 0;
    while ((i = classString.find(" ")) != std::string::npos) {
      std::string c = classString.substr(0, i);
      classMap[c] = true;
      classString.erase(0, i + 1);
    }
     classMap[classString] = true;
  } 
  return classMap;
}

Element::Element(std::string tn) {
  tag_name = tn;
}