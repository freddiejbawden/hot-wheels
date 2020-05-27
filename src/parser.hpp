#include <string>

class Parser {
  public:
    int inputPos;
    std::string input;
    std::string commentOpen;
    std::string commentClose;
    bool checkForComment();
    void skipWhitespace();
    char getCurrentChar();
    void consumeComment();
    Parser() = default;
};
