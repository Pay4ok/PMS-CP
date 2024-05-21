#include "GraphicItem.h"

GraphicItem::GraphicItem(int w, int h) : width(w), height(h) {
  points.resize(width * height);
  for (int i = 0; i < width * height; ++i) {
    points[i] = 0;
  }
}

void GraphicItem::animate(){
  
}