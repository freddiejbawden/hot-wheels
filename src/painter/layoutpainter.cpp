#include "layoutpainter.hpp"
#include "../domnodes/element.hpp"
#include "../domnodes/text.hpp"
#include <SDL2/SDL_ttf.h>
#include "../css/cssnodes/values/color.hpp"
#include "../layout/fontmanager/fontmanager.hpp"
#include <cstdlib>
LayoutPainter::LayoutPainter(LayoutBox* l, Dimensions viewport) {
  layout = l;
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    printf("error initializing SDL: %s\n", SDL_GetError());
  }
  printf("Init Successful!\n");


  SDL_Window* win = SDL_CreateWindow("Intel8080",
                                      SDL_WINDOWPOS_UNDEFINED, 
                                      SDL_WINDOWPOS_UNDEFINED, 
                                      500,
                                      500, SDL_WINDOW_SHOWN
                                      );
    if (!win) {
      printf("error creating window: %s\n", SDL_GetError());
      SDL_Quit();
      exit(1);
  }
  window = win;
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawColor(renderer, 255,255,255,255);
  SDL_RenderClear(renderer );
}

void LayoutPainter::setColor(Color* c) {
  SDL_SetRenderDrawColor(renderer, c->r, c->g, c->b, c->a);
}


void LayoutPainter::drawLayoutBox(LayoutBox* layout){
  SDL_Rect r;
  if (layout->node != NULL) {
    Color *c = (Color*) layout->node->getPropertyValue("background-color");
    if (c == NULL) {
        SDL_SetRenderDrawColor( renderer, 255,255,255,255);
    } else {
      setColor(c);
    }
    if (typeid(*(layout->node->node)) == typeid(Element)) {
      Element* elm = (Element*) layout->node->node;
      std::cout << "painting " << elm->tag_name << "\n";
      r.x = layout->dimensions.content.x;
      r.y = layout->dimensions.content.y;
      r.w = layout->dimensions.content.width;
      r.h = layout->dimensions.content.height;
      SDL_RenderFillRect(renderer, &r);
    } else if (typeid(*(layout->node->node)) == typeid(Text)) {
      Text* t = (Text*) layout->node->node;
      SDL_Color black = {0, 0, 0}; 
      FontManager* fm = FontManager::getInstance();
      SDL_Surface* textSurface = TTF_RenderText_Solid(fm->getFont("arial16"), t->text.c_str(), black);
      SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface); 
      r.x = layout->dimensions.content.x;
      r.y = layout->dimensions.content.y;
      r.w = layout->dimensions.content.width;
      r.h = layout->dimensions.content.height;
      SDL_RenderCopy(renderer, textTexture, NULL, &r);
    }
  
  } 
  
  for (std::vector<LayoutBox*>::iterator it = layout->children.begin(); it != layout->children.end(); ++it) {
    drawLayoutBox(*it);
  }
}

void LayoutPainter::hold() {
  SDL_RenderPresent(renderer);

  SDL_Event e;
  bool quit = false;
  while (!quit){
      while (SDL_PollEvent(&e)){
          if (e.type == SDL_QUIT){
              quit = true;
          }
          if (e.type == SDL_WINDOWEVENT){
            if (e.window.event == SDL_WINDOWEVENT_CLOSE) {

              quit = true;
            }
          }
      }
  }
}
