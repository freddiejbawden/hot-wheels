#include <ctype.h>
#include <vector>
#include <stdio.h>
#include <cassert>
#include "parser.hpp"
#include "../nodes/node.hpp"
#include "../nodes/text.hpp"
#include "../nodes/element.hpp"

char HTMLParser::getCurrentChar() {
  return input.at(inputPos);
}

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
    if (input.substr(inputPos, 2) == "</") {
      break;
    }
    Node* n = parseNode();
    nodes.push_back(n);
  }
  return nodes;
}

Node* HTMLParser::parseElement() {
  // element := TAG | TAG ATTRIBUTE
  Node* currentNode;
  std::string tag_name;
  tag_name = parseTagName();
  currentNode = new Element(tag_name);
  skipWhitespace();
  if (getCurrentChar() == '>') {
    inputPos++;
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

void HTMLParser::skipWhitespace() {
  int i = 0;
  char c = getCurrentChar();
  if (isspace(c)) {
    i += 1;
    inputPos++;
    c = getCurrentChar();
  }
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


Node* HTMLParser::parse(std::string inp) {
  Node root = Node();
  inputPos = 0;
  input = inp;
  root = Node();
  std::vector<Node*> n = parseNodes();
  return n[0];
} 
HTMLParser::HTMLParser() {
  inputPos = 0;
}