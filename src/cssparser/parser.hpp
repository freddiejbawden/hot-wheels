#include <string>
#include "../cssnodes/selectors/simple_selector.hpp"
#include "../cssnodes/rule.hpp"

class CSSParser {
  public:
    int inputPos;
    std::string input;
    std::string parseIdentifier();
    SimpleSelector* parseSimpleSelector();
    std::vector<Rule*> parse();
    char getCurrentChar();
};