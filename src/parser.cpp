
#include "parser.hpp"

char Parser::getCurrentChar() {
  return input.at(inputPos);
}

bool Parser::checkForComment() {
  return (input.substr(inputPos, commentOpen.size()) == commentOpen);
}
void Parser::skipWhitespace() {
  char c = getCurrentChar();
  while (isspace(c)) {
    inputPos++;
    c = getCurrentChar();
  }
}

void Parser::consumeComment() {
  while (input.substr(inputPos, commentClose.size()) != commentClose) {
          inputPos++;
  }
  inputPos+=3;
}
