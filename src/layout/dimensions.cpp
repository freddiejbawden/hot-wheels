#include "dimensions.hpp"
#include <iostream>
Rect* Dimensions::paddingBox() {
  return content.expandedBy(padding);
}

Rect* Dimensions::borderBox() {
  Rect* p = paddingBox();
  return p->expandedBy(border);
}

Rect* Dimensions::marginBox() {
  return borderBox()->expandedBy(margin);
}