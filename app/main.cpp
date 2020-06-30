#include <iostream>
#include "domnodes/text.hpp"
#include "preprocessor/preprocessor.hpp"
#include "htmlparser/htmlparser.hpp"
#include "cssparser/cssparser.hpp"
#include "domnodes/element.hpp"
#include "styletree/styletree.hpp"
#include "layout/blockBox.hpp"
#include "layoutpainter/layoutpainter.hpp"

int main() {
  std::cout << "Hot wheels\n";
  std::string htmldata = Preprocessor::loadAndCleanFile("test.html");
  HTMLParser htmlParser = HTMLParser();
  std::string cssStrings = "";
  Node* root = htmlParser.parse(htmldata, &cssStrings);
  cssStrings = Preprocessor::cleanFile(cssStrings);
  std::cout << cssStrings << '\n';
  std::cout << "test.html parsed\n";
  
  std::string css_data = Preprocessor::loadAndCleanFile("test.css");
  CSSParser cssParser = CSSParser();
  css_data = css_data + cssStrings;
  std::cout << css_data << '\n';
  std::vector<Rule*> rules = cssParser.parse(css_data);
  std::cout << "CSS parsed\n";
  // Properly merge rules  
  
  StyledNode* rootStyledNode = new StyledNode(root, rules);
  std::cout << "style tree compiled\n";
  rootStyledNode->display(0);
  
  LayoutBox* layoutBox = new BlockBox(rootStyledNode);
  Dimensions viewport = Dimensions();
  viewport.content = Rect();
  viewport.content.width = 500;
  viewport.content.height = 0;
  layoutBox->createLayout(viewport);
  std::cout << "Layout boxes computed\n";
  layoutBox->display(0);
  
  LayoutPainter* painter = new LayoutPainter(layoutBox, viewport);
  painter->drawLayoutBox(layoutBox);
  painter->hold();
  

}