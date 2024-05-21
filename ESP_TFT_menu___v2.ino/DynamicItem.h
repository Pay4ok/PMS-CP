#pragma once
#include <vector>
#include "GraphicItem.h"
#include "TFT_eSPI_HEADERS.h"

class DynamicItem
{
protected:
  static bool is_handler_started;
  static struct HandleItemType {
    GraphicItem *item;
    unsigned int delay;
    TimerHandle_t timer;
  } HandleItem;
public:
  static void add_item(GraphicItem* item, unsigned int delay);
  static std::vector<HandleItemType> handle_items;
  static int HandlerStart();
  static void Handler();
  static void remove_item(int id);
  static int ApplyHandlerChanges();
};
