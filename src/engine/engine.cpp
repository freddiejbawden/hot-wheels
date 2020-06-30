#include "engine/engine.hpp"
#include <iostream>
#include "domnodes/text.hpp"
#include "preprocessor/preprocessor.hpp"
#include "htmlparser/htmlparser.hpp"
#include "cssparser/cssparser.hpp"
#include "domnodes/element.hpp"
#include "styletree/styletree.hpp"
#include "layout/blockBox.hpp"
#include "layoutpainter/layoutpainter.hpp"


void Engine::render(std::string htmlFile, std::string cssFile) {

  // Parse HTML File and create DOM tree
  std::string htmldata = Preprocessor::loadAndCleanFile(htmlFile);
  HTMLParser htmlParser = HTMLParser();
  std::string cssStrings = "";
  Node* root = htmlParser.parse(htmldata, &cssStrings);
  std::cout << "HTML Parsed\n";

  // Parse CSS and create list of rules
  std::string cssInHTML = Preprocessor::cleanFile(cssStrings);
  std::string css_data = Preprocessor::loadAndCleanFile(cssFile);
  CSSParser cssParser = CSSParser();
  css_data = css_data + cssInHTML;
  std::vector<Rule*> rules = cssParser.parse(css_data);
  std::cout << "CSS parsed\n";
  
  // Combine DOM and list of rules into styled nodes
  StyledNode* rootStyledNode = new StyledNode(root, rules);
  rootStyledNode->display(0);
  std::cout << "Style tree compiled\n";
  
  // Calculate the dimensions of the elements according to their styles
  LayoutBox* layoutBox = new BlockBox(rootStyledNode);
  Dimensions viewport = Dimensions();
  viewport.content = Rect();
  viewport.content.width = 600;
  viewport.content.height = 0;
  layoutBox->createLayout(viewport);
  layoutBox->display(0);
  std::cout << "Layout boxes computed\n";
  

  // Paint the layout
  LayoutPainter* painter = new LayoutPainter(layoutBox, viewport);
  painter->drawLayoutBox(layoutBox);
  painter->hold();
}