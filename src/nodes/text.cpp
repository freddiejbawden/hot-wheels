#include "text.hpp"

void Text::display() {
  std::cout << "(Text: " << text << ")\n";
}

Text::Text(std::string content) {
  text = content;
}