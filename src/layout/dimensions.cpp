#include "dimensions.hpp"

Rect* Dimensions::paddingBox() {
  return content.expandedBy(padding);
}

Rect* Dimensions::borderBox() {
  return paddingBox()->expandedBy(border);
}

Rect* Dimensions::marginBox() {
  return borderBox()->expandedBy(margin);
}