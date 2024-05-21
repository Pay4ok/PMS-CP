#pragma once
#include "GraphicItem.h"

class SpinnerGraphicitem :
    public GraphicItem
{
public:
  SpinnerGraphicitem(int w, int h);
  void draw();
  void clear();
  void animate();
};