#pragma once
#include "Menu.h"
#include <vector>

class GraphicItem {
public:
  int width, height, anim_iteration;
  std::vector<short unsigned int> points;
  Menu* parent;
  GraphicItem(int w, int h);
  void draw();
  void clear();
  void animate();
};

