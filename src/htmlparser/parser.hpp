#pragma once
#ifndef HTML_PARSER
#define HTML_PARSER
#include <string>
#include "../nodes/node.hpp"
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
    void parseAttribute();
    HTMLParser();
};
 

#endif