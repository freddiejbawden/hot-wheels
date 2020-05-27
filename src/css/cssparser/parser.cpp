#include "parser.hpp"


// TODO: combine HTMLParser and CSSParser to share utilities 
// through inheritence

char CSSParser::getCurrentChar() {
  return input.at(inputPos);
}
  
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

std::vector<Selector*> CSSParser::parseSelectors() {
  std::vector<Selector*> selectors;
  while (getCurrentChar() != '{') {
  }
}

std::vector<Rule*> CSSParser::parse()
{
  std::vector<Rule*> rules;
  parseSelectors();
  return rules;
}
CSSParser::CSSParser() {
  inputPos = 0;
  commentOpen = "/*";
  commentClose = "*/";
}