#pragma once
#ifndef HTML_PARSER
#define HTML_PARSER
#include <string>
#include "domnodes/node.hpp"
#include "domnodes/element.hpp"
#include "parser/parser.hpp"

class HTMLParser : public Parser {
 public:
    Node *root;
    std::string* cssRules;
    bool isStyle = false;
    Node* parse(std::string inp, std::string* cssRules);
    Node* parseNode();
    std::vector<Node*> parseNodes();
    Node* parseElement();
    std::string parseTagName();
    Node* parseText();
    char getNextChar();
    std::string parseAttributeKey();
    void checkForDoctype();
    void parseAttributes(Element *n);
    std::string parseAttributeValue();
    HTMLParser();
};
 

#endif