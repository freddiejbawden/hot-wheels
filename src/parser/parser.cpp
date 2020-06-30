#include <iostream>
#include "parser/parser.hpp"

char Parser::getCurrentChar() {
  if (inputPos >= input.length()) {
    return ' ';
  }
  return input.at(inputPos);
}

bool Parser::checkForComment() {
  return (input.substr(inputPos, commentOpen.size()) == commentOpen);
}
void Parser::skipWhitespace() {
  if (inputPos > input.length()) {
    std::cout<< "dropout\n";
    return;
  }
  char c = getCurrentChar();
  while (isspace(c)) {
    inputPos++;
    if (inputPos >= input.length()) {
      break;
    }
    c = getCurrentChar();
  }
}

void Parser::consumeComment() {
  while (input.substr(inputPos, commentClose.size()) != commentClose) {
          inputPos++;
  }
  inputPos+=3;
}
