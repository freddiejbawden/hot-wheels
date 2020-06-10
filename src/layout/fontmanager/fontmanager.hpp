#pragma once
#ifndef FONTMANAGER
#define FONTMANAGER
#include <SDL2/SDL_ttf.h>
#include <string>
#include <unordered_map>

class FontManager {
  public:
    static FontManager* getInstance();
    int getWidthOfText(std::string font, std::string text);
    int getHeightOfText(std::string font, std::string text);
    TTF_Font* getFont(std::string font);
  private:
    static FontManager* instance;
    FontManager();
    std::unordered_map<std::string, TTF_Font*> fonts;
};

#endif

