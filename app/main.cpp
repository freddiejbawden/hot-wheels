#include "engine/engine.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  std::string htmlFile;
  std::string cssFile;

  if (argc >= 2) {
    htmlFile = argv[1];
  } else {
    std::cout << "Please include a path to a HTML file!\n";
    exit(1);
  }
  if (argc >= 3) {
    cssFile = argv[2];
  }
  Engine::render(htmlFile, cssFile);
}