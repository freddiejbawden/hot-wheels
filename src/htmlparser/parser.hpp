#pragma once
#ifndef HTML_PARSER
#define HTML_PARSER
#include <string>
#include "../domnodes/node.hpp"
#include "../domnodes/element.hpp"

class HTMLParser {
 public:
    int inputPos;
    std::string input;
    Node *root;
    Node* parse(std::string inp);
    Node* parseNode();
    std::vector<Node*> parseNodes();
    Node* parseElement();
    std::string parseTagName();
    Node* parseText();
    char getNextChar();
    char getCurrentChar();
    void skipWhitespace();
    std::string parseAttributeKey();
    void checkForDoctype();
    void parseAttributes(Element *n);
    std::string parseAttributeValue();
    HTMLParser();
};
 

#endif