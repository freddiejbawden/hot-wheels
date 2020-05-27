#pragma once
#ifndef TEXT
#define TEXT
#include "node.hpp"

class Text: public Node {
  public:
    std::string text;
    void display(int level);
    Text(std::string content);
};
#endif
