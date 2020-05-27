#include "parser.hpp"

char CSSParser::getCurrentChar() {
  return input.at(inputPos);
}
  
std::string CSSParser::parseIdentifier() 
{

}

SimpleSelector* CSSParser::parseSimpleSelector() 
{
  SimpleSelector *selector = new SimpleSelector();

}

std::vector<Rule*> CSSParser::parse()
{
  
}