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
    std::string getId();
    std::unordered_map<std::string, bool>  getClasses();
    void addAttribute(std::string attribute_name, std::string attribute_value);
    std::string getAttribute(std::string attribute_name);
    Element(std::string tn);
};

#endif