#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include <SDL_ttf.h>
#include "fontmanager/fontmanager.hpp"

FontManager* FontManager::instance = 0;
int FontManager::DEFAULT_TEXTSIZE = 16;
FontManager* FontManager::getInstance() {
  if (instance == 0)
  {
    instance = new FontManager();
  }
  return instance;
}

FontManager::FontManager() {
  if(TTF_Init() == -1 )
  {
      std::cout << "Failed to init SDL_TTF\n";
      exit(1);
  }
  std::cout << "Font init complete!\n";
  fonts.emplace("arial16", TTF_OpenFont("src/fontmanager/Arial.ttf", 16));

};

TTF_Font* FontManager::getFont(std::string fontname, int size) {
  std::string key = fontname + std::to_string(size);
  if (fonts.find(key) == fonts.end()) {
    // assume arial for now
    fonts.emplace(key, TTF_OpenFont("src/fontmanager/Arial.ttf", size));
  }
  return fonts[key];
}

int FontManager::getWidthOfText(std::string font, int size, std::string text) {
  int w;
  int h;
  std::transform(font.begin(), font.end(), font.begin(),
    [](unsigned char c){ return std::tolower(c); });
  TTF_Font *f = getFont(font, size);
  TTF_SizeText(f, text.c_str(), &w, &h);
  return w;
}

int FontManager::getHeightOfText(std::string font, int size, std::string text) {
  int w;
  int h;
  std::transform(font.begin(), font.end(), font.begin(),
    [](unsigned char c){ return std::tolower(c); });
  TTF_Font *f = getFont(font, size);
  TTF_SizeText(f, text.c_str(), &w, &h);
  return h;
}