#include <string>
#pragma once
#ifndef PREPROCESSOR
#define PREPROCESSOR

class Preprocessor {
  public:
    static std::string loadAndCleanFile(std::string filename);    
    static std::string cleanFile(std::string content);
};

#endif