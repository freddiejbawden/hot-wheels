#include "domnodes/text.hpp"

void Text::display(int level) {
  std::cout << "\"" << text << "\"";
}

Text::Text(std::string content) {
  text = content;
}