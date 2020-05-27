#include "parser.hpp"
#include <iostream>
  
std::string CSSParser::parseIdentifier() 
{
  std::string identifier = "";
  while(isalnum(getCurrentChar())) {
    identifier.push_back(getCurrentChar());
    inputPos++;
  }
  return identifier;
}

SimpleSelector* CSSParser::parseSimpleSelector() 
{
  SimpleSelector *selector = new SimpleSelector();
  selector->is_universal = false;
  while (inputPos < input.size()) {
    skipWhitespace();
    char c = getCurrentChar();
    if (c == '#') { 
      inputPos++;
      selector->id = parseIdentifier();
    } else if (c == '.') {
      inputPos++;
      selector->classes.push_back(parseIdentifier());
    } else if (c == '*') {
      inputPos++;
      selector->is_universal = true;
    } else if (isalnum(c)) {
      selector->tag_name = parseIdentifier();
    } else {
      break;
    }
  }
  return selector;

}

void CSSParser::skipToChar(char c) {
  while(getCurrentChar() != c) {
    inputPos++;
  }
}

std::vector<Selector*> CSSParser::parseSelectors() {
  std::vector<Selector*> selectors;
  while (getCurrentChar() != '{') {
    selectors.push_back(parseSimpleSelector());
    skipWhitespace();
    if (getCurrentChar() == ',') {
      inputPos++;
    } else if (getCurrentChar() == '{') {
      break;
    } else {
      std::cout << "Error\n";
      skipToChar('{');
      inputPos++;
      // this is an error, selectors must be divided by commas
      std::vector<Selector*> empty; 
      return empty;
    }
  }
  inputPos++;
  return selectors;
}


Declaration CSSParser::parseDeclaration() {
  Declaration d = Declaration();
  return d;
  
}

std::vector<Declaration> CSSParser::parseDeclarations() {
  std::vector<Declaration> declarations;
  while (getCurrentChar() != '}') {
    declarations.push_back(parseDeclaration());
  }
  inputPos++;
  return declarations;
}

std::vector<Rule*> CSSParser::parse(std::string data)
{
  inputPos = 0;
  input = data;
  std::vector<Rule*> rules;
  while (inputPos < input.size()) {
   Rule* r = new Rule();
   r->selectors = parseSelectors(); 
   r->declarations = parseDeclarations();
   r->display();
  }
  return rules;
}
CSSParser::CSSParser() {
  inputPos = 0;
  commentOpen = "/*";
  commentClose = "*/";
}