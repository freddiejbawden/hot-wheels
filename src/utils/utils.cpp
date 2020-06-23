#include "utils/utils.hpp"
#include <iostream>

namespace utils {
  void splitString(std::string t, std::vector<std::string>* out) {
    std::string text = t;
    size_t pos = 0;
    // make this a util function
    std::string token;
    while ((pos = text.find(' ')) != std::string::npos) {
      token = text.substr(0, pos + 1);
      out->push_back(token);
      text.erase(0, pos + 1);
    }
    token = text;
    out->push_back(token);
  }
}