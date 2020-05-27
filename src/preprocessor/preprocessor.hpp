#include <string>
#pragma once
#ifndef PREPROCESSOR
#define PREPROCESSOR

class Preprocessor {
  public:
    static std::string loadFile(std::string filename);    
};

#endif