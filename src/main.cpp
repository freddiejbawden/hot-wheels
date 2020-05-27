#include <iostream>
#include "nodes/element.hpp"
#include "nodes/text.hpp"
#include "preprocessor/preprocessor.hpp"
#include "htmlparser/parser.hpp"

int main() {
  std::cout << "Hot wheels\n";
  std::string data = HTMLPreprocessor::loadFile("test.html");
  std::cout << data << '\n';
  HTMLParser htmlParser = HTMLParser();
  Node* root = htmlParser.parse(data);
  root->display(0);
}