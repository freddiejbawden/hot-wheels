#include <iostream>
#include <cassert>

#include "cssparser/cssparser.hpp"
#include "cssnodes/values/length.hpp"
#include "cssnodes/values/color.hpp"
#include "cssnodes/values/keyword.hpp"


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

Unit CSSParser::getUnit() {
  std::string unittext;
  while (getCurrentChar() != ';') {
    unittext.push_back(getCurrentChar());
    inputPos++;
  }
  if (unittext == "px") {
    return px;
  } else {
    return invalid;
  }
}

std::string CSSParser::parseDeclarationKey() {
  std::string key;
  while (getCurrentChar() != ':' && getCurrentChar() != ';') {
    key.push_back(getCurrentChar());
    inputPos++;
  }
  return key;
}

uint8_t CSSParser::getColorComponent() {
  std::string colorvalue = "";
  colorvalue.push_back(getCurrentChar());
  inputPos++;
  colorvalue.push_back(getCurrentChar());
  inputPos++;
  uint8_t intvalue = std::stoul(colorvalue, nullptr, 16);
  return intvalue;
}

Value* CSSParser::parseDeclarationValue() {
  if (isnumber(getCurrentChar())) {
    std::string value;
    value.push_back(getCurrentChar());
    inputPos++;
    bool dot_seen = false;
    while (isnumber(getCurrentChar()) || getCurrentChar() == '.') {
      value.push_back(getCurrentChar());
      inputPos++;
    }
    Length* l = new Length();
    l->value = std::stof(value);
    l->unit = getUnit();
    inputPos++;
    return l;
  } else if (getCurrentChar() == '#') {
    inputPos++;
    Color* color = new Color();
    //TODO: handle malformed input
    color->r = getColorComponent();
    color->g = getColorComponent();
    color->b = getColorComponent();
    color->a = (getCurrentChar() == ';') ? 255 : getColorComponent();
    inputPos++;
    return color;
  } else {
    // must be key word
    if (getCurrentChar() == '"') {
      inputPos++;
    }
    std::string keyword;
    while (getCurrentChar() != ';') {
      keyword.push_back(getCurrentChar());
      inputPos++;
    }
    inputPos++;
    Keyword* word = new Keyword();
    word->value = keyword;
    return word;
  }
 }

Declaration CSSParser::parseDeclaration() {
  Declaration d = Declaration();
  skipWhitespace();
  std::string key =  parseDeclarationKey();
  assert(getCurrentChar() == ':');
  inputPos++;
  skipWhitespace();
  Value *v = parseDeclarationValue();
  d.name = key;
  d.value = v; 
  return d; 
}  


std::vector<Declaration> CSSParser::parseDeclarations() {
  std::vector<Declaration> declarations;
  skipWhitespace();
  while (getCurrentChar() != '}') {
    declarations.push_back(parseDeclaration());
    skipWhitespace();
  }
  inputPos++;
  return declarations;
}

std::vector<Rule*> CSSParser::parse(std::string data)
{
  inputPos = 0;
  input = data;
  std::vector<Rule*> rules;
  std::cout << input << ": " << input.length() << '\n';
  while (inputPos < input.length()) {
    std::cout << "new rule\n";
    Rule* r = new Rule();
    r->selectors = parseSelectors(); 
    r->declarations = parseDeclarations();
    r->display();
    rules.push_back(r);
    skipWhitespace();
  }
  std::cout << "done\n";
  return rules;
}
CSSParser::CSSParser() {
  inputPos = 0;
  commentOpen = "/*";
  commentClose = "*/";
}