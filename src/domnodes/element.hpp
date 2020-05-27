#pragma once
#ifndef ELEMENT
#define ELEMENT
#include "node.hpp"
#include <unordered_map>

class Element: public Node {
  public:
    std::string tag_name;
    std::unordered_map<std::string, std::string> attributes;
    void displayAttributes();
    void display(int level);    
    void addAttribute(std::string attribute_name, std::string attribute_value);
    Element(std::string tn);
};

#endif