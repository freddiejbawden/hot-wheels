#include <iostream>
#include "domnodes/text.hpp"
#include "preprocessor/preprocessor.hpp"
#include "htmlparser/parser.hpp"
#include "css/cssparser/parser.hpp"
#include "domnodes/element.hpp"
#include "styletree/styletree.hpp"
#include "layout/blockBox.hpp"
#include "painter/layoutpainter.hpp"

int main() {
  std::cout << "Hot wheels\n";
  std::string htmldata = Preprocessor::loadFile("test.html");
  HTMLParser htmlParser = HTMLParser();
  Node* root = htmlParser.parse(htmldata);
  std::cout << "test.html parsed\n";
  
  std::string css_data = Preprocessor::loadFile("test.css");
  CSSParser cssParser = CSSParser();
  std::vector<Rule*> rules = cssParser.parse(css_data);
  std::cout << "test.css parsed\n";

  StyledNode* rootStyledNode = new StyledNode(root, rules);
  std::cout << "style tree compiled\n";
  rootStyledNode->display(0);
  LayoutBox* layoutBox = new BlockBox(rootStyledNode);
  std::cout << "Layout boxes computed\n";
  layoutBox->display(0);
  Dimensions viewport = Dimensions();
  viewport.content = Rect();
  viewport.content.width = 500;
  viewport.content.height = 500;
  layoutBox->createLayout(viewport);
  LayoutPainter* painter = new LayoutPainter(layoutBox, viewport);
  painter->drawLayoutBox(layoutBox);
  painter->hold();

}