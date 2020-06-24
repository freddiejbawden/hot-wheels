#include "domnodes/text.hpp"

void Text::display(int level) {
  if (text.length() > 40) {
    std::cout << '"' << text.substr(0,40) << "...\"";
  } else {
    std::cout << '"' << text << '"';
  }
}

Text::Text(std::string content) {
  text = content;
}