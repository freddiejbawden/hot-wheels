#include <string>
#pragma once
#ifndef PREPROCESSOR
#define PREPROCESSOR

class HTMLPreprocessor {
  public:
    static std::string loadFile(std::string filename);    
};

#endif