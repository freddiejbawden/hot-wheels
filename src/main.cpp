#include <iostream>
#include "domnodes/text.hpp"
#include "preprocessor/preprocessor.hpp"
#include "htmlparser/parser.hpp"
#include "css/cssparser/parser.hpp"


int main() {
  std::cout << "Hot wheels\n";
  // std::string data = Preprocessor::loadFile("test.html");

/*   HTMLParser htmlParser = HTMLParser();
  Node* root = htmlParser.parse(data);
  std::cout << "test.html parsed\n"; */


  std::string css_data = Preprocessor::loadFile("test.css");
  CSSParser cssParser = CSSParser();
  cssParser.parse(css_data);



}