#include "fontmanager.hpp"
#include <iostream>
FontManager* FontManager::instance = 0;

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
  fonts.emplace("arial16", TTF_OpenFont("src/layout/fontmanager/Arial.ttf", 16));

};

TTF_Font* FontManager::getFont(std::string font) {
  return fonts[font];
}

int FontManager::getWidthOfText(std::string font, std::string text) {
  int w;
  int h;
  TTF_Font *f = fonts[font];
  TTF_SizeText(f, text.c_str(), &w, &h);
  return w;
}

int FontManager::getHeightOfText(std::string font, std::string text) {
  int w;
  int h;
  TTF_Font *f = fonts[font];
  TTF_SizeText(f, text.c_str(), &w, &h);
  return h;
}