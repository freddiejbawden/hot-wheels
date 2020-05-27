#pragma once
#ifndef CSS_PARSER
#define CSS_PARSER
#include <string>
#include "../cssnodes/selectors/simple_selector.hpp"
#include "../cssnodes/rule.hpp"
#include "../../parser.hpp"
class CSSParser: public Parser {
  public:
    std::string parseIdentifier();
    SimpleSelector* parseSimpleSelector();
    std::vector<Selector*> parseSelectors();
    std::vector<Rule*> parse(std::string data);
    std::vector<Declaration> parseDeclarations();
    Declaration parseDeclaration();
    void skipToChar(char c);
    CSSParser();
};
#endif