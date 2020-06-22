#pragma once
#ifndef FONTMANAGER
#define FONTMANAGER
#include <SDL_ttf.h>
#include <string>
#include <unordered_map>

class FontManager {
  public:
    static FontManager* getInstance();
    int getWidthOfText(std::string font,int size, std::string text);
    int getHeightOfText(std::string font, int size, std::string text);
    TTF_Font* getFont(std::string font, int size);
  private:
    static FontManager* instance;
    FontManager();
    std::unordered_map<std::string, TTF_Font*> fonts;
};

#endif

