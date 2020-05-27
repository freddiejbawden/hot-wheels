#include <string>
#include "../cssnodes/selectors/simple_selector.hpp"
#include "../cssnodes/rule.hpp"
#include "../../parser.hpp"
class CSSParser: public Parser {
  public:
    int inputPos;
    std::string input;
    std::string parseIdentifier();
    SimpleSelector* parseSimpleSelector();
    std::vector<Selector*> parseSelectors();
    std::vector<Rule*> parse();
    char getCurrentChar();
    CSSParser();
};