#include <iostream>
#include "domnodes/text.hpp"
#include "preprocessor/preprocessor.hpp"
#include "htmlparser/parser.hpp"

int main() {
  std::cout << "Hot wheels\n";
  std::string data = HTMLPreprocessor::loadFile("test.html");
  HTMLParser htmlParser = HTMLParser();
  Node* root = htmlParser.parse(data);
  root->display(0);
}