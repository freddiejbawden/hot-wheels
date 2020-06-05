#pragma once
#ifndef CSS_COLOR
#define CSS_COLOR
#include <cstdint>
#include "value.hpp"

class Color : public Value {
  public:
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
    Color() = default;
    void display();
    float toPX();
};
#endif