#include <ctype.h>
#include <vector>
#include <stdio.h>
#include <cassert>
#include <algorithm>
#include "htmlparser/htmlparser.hpp"
#include "domnodes/node.hpp"
#include "domnodes/text.hpp"
#include "domnodes/element.hpp"


Node* HTMLParser::parseNode() {
  
  char current = getCurrentChar();
  if (current == '<') {
    return parseElement();
  } else {
    return parseText();
  }
}


std::vector<Node*> HTMLParser::parseNodes() {
  std::vector<Node*> nodes;
  while (inputPos < input.size()) {
    skipWhitespace();
    // check for end
    if (checkForComment()) {
      consumeComment();
      continue;
    }
    if (input.substr(inputPos, 2) == "</") {
      break;
    }
    Node* n = parseNode();
    nodes.push_back(n);
  }
  return nodes;
}

std::string HTMLParser::parseAttributeValue() {
  std::string value = "";
  int quoteCount = 0; 
  while (quoteCount < 2) {
    if (getCurrentChar() != '"') {
     value.push_back(getCurrentChar());
    } else {
      quoteCount++;
    }
    inputPos++;
  }
  return value;
}

std::string HTMLParser::parseAttributeKey() {
  std::string value = "";
  int quoteCount = 0; 
  while (getCurrentChar() != '=' && getCurrentChar() != '>') {
    if (getCurrentChar() != '"') {
     value.push_back(getCurrentChar());
    } else {
      quoteCount++;
    }
    inputPos++;
  }
  return value;
}

void HTMLParser::parseAttributes(Element *n){
  while(getCurrentChar() != '>') {
    skipWhitespace();
    std::string key = parseAttributeKey();
    assert(key != "");
    //sanity check
    assert(getCurrentChar() == '=');
    inputPos++;
    std::string value = parseAttributeValue();
    assert(value != "");
    n->addAttribute(key, value);
  }
  inputPos++;
}

Node* HTMLParser::parseElement() {
  // element := TAG | TAG ATTRIBUTE
  std::string tag_name;
  tag_name = parseTagName();
  Element *currentNode = new Element(tag_name);
  skipWhitespace();
  if (getCurrentChar() == '>') {
    inputPos++;
  } else {
    parseAttributes(currentNode);
  }

  // recursive call to construct a tree with currentNode
  // as the root
  std::vector<Node*> children = parseNodes();
  currentNode->children = children;

  // check that thhere is a closing tag and it maches he current 
  assert(getCurrentChar() == '<');
  inputPos++;
  assert(getCurrentChar() == '/');
  assert(parseTagName() == tag_name);
  assert(getCurrentChar() == '>');
  inputPos++;
  return currentNode;
}


std::string HTMLParser::parseTagName() {
   std::string tag;
   inputPos++;
   char c = getCurrentChar();
   while (isalnum(c)) {
     tag.push_back(c);
     inputPos++;
     c = getCurrentChar();
   }
   // roll back
   return tag;
}

Node* HTMLParser::parseText() {
  std::string t;
  char current = getCurrentChar();
  while (current != '<') {
    t.push_back(current);
    inputPos++;
    current = getCurrentChar();
  }
  Text* textNode = new Text(t);
  return textNode;
}

void HTMLParser::checkForDoctype() {
  bool docTypeProcessed = false;
  while (!docTypeProcessed) {
    if (input.substr(inputPos, 2) == "<!") {
      inputPos++;
      std::string s = parseTagName();
      std::transform(s.begin(), s.end(),s.begin(), ::toupper);
      if (s == "DOCTYPE") {
        std::string doctype_value = parseTagName();
        assert(doctype_value == "html");
        assert(getCurrentChar() == '>');
        inputPos++;
      } else {
        consumeComment();
      }
    } else {
      docTypeProcessed = true;
    }
  }
}

Node* HTMLParser::parse(std::string inp) {
  Node root = Node();
  inputPos = 0;
  input = inp;
  checkForDoctype();
  std::vector<Node*> n = parseNodes();
  return n[0];
} 
HTMLParser::HTMLParser() {
  inputPos = 0;
  commentOpen = "<!--";
  commentClose = "-->";
}