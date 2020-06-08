#include "rect.hpp"

Rect* Rect::expandedBy(EdgeSizes edge) {
  Rect* toReturn = new Rect();
  toReturn->x = x - edge.left;
  toReturn->y = y - edge.top;
  toReturn->width = width + edge.left + edge.right;
  toReturn->height = height + edge.top + edge.bottom;
  return toReturn;
}