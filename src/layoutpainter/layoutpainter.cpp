
#include <SDL_ttf.h>

#include "layoutpainter/layoutpainter.hpp"
#include "domnodes/element.hpp"
#include "domnodes/text.hpp"
#include "cssnodes/values/color.hpp"
#include "fontmanager/fontmanager.hpp"
#include "utils/utils.hpp"

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

void splitIntoLines(std::string text, int fontsize, Dimensions container, std::vector<std::string>* lines) {
  int currentWidth = 0;

  std::vector<std::string> out;
  size_t pos = 0;
  
  FontManager* fm = FontManager::getInstance();
  std::string currentLine = "";
  bool endofline = false;
  utils::splitString(text, &out);
  std::string token;
  for (std::vector<std::string>::iterator it = out.begin(); it != out.end(); ++it) {
    token = (*it);
    int wordWidth = fm->getWidthOfText("arial", fontsize, token);
    if (currentWidth + wordWidth > container.content.width) {
      lines->push_back(currentLine);
      currentLine = token;
      currentWidth = wordWidth;
    } else {
      currentLine += token;
      currentWidth += wordWidth;
    } 
  }
  lines->push_back(currentLine);
}


void LayoutPainter::drawLayoutBox(LayoutBox* layout){
  SDL_Rect r;
  if (layout->node != NULL) {
    Color *c = (Color*) layout->node->getPropertyValue("background-color");
    bool background = false;
    if (c != NULL) {
      background = true;
      setColor(c);
    }
    if (typeid(*(layout->node->node)) == typeid(Element)) {
      Element* elm = (Element*) layout->node->node;
      r.x = layout->dimensions.content.x;
      r.y = layout->dimensions.content.y;
      r.w = layout->dimensions.content.width;
      r.h = layout->dimensions.content.height;
      if (background) SDL_RenderFillRect(renderer, &r);
    } else if (typeid(*(layout->node->node)) == typeid(Text)) {
      Text* t = (Text*) layout->node->node;
      SDL_Color black = {0, 0, 0}; 
      FontManager* fm = FontManager::getInstance();
      int fontsize = layout->node->parent->getPropertyValue("font-size")->toPX();
      std::vector<std::string> lines;
      splitIntoLines(t->text, fontsize, layout->dimensions, &lines);
      int y = layout->dimensions.content.y;
      for (std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); ++it) {
        const char* content = (*it).c_str();
        SDL_Surface* textSurface = TTF_RenderText_Solid(fm->getFont("arial", fontsize), content, black);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface); 
        r.x = layout->dimensions.content.x;
        r.y = y;
        r.w = fm->getWidthOfText("arial", fontsize, content);
        r.h = fm->getHeightOfText("arial", fontsize, content);
        SDL_RenderCopy(renderer, textTexture, NULL, &r);
        y += fm->getHeightOfText("arial", fontsize, content);
      };
      
     
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
