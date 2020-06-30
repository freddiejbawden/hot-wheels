#pragma once
#ifndef ENGINE
#define ENGINE

#include <string>

class Engine {
  public:
    static void render(std::string htmlFile, std::string cssFile = ""); 
};

#endif