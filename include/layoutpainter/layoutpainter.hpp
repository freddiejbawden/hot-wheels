#pragma once
#ifndef PAINTER
#define PAINTER
#include "SDL.h"
#include "layout/layoutBox.hpp"
#include "cssnodes/values/color.hpp"
class LayoutPainter {
  public: 
    LayoutBox* layout;
    SDL_Window* window;
    SDL_Renderer* renderer;
    void drawLayoutBox(LayoutBox* l);
    void drawChildren(LayoutBox* l);
    void setColor(Color* c);

    void hold();
    LayoutPainter(LayoutBox* l, Dimensions viewport);
};

#endif