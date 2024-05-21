#include "DynamicItem.h"
#include "TriangleGraphicItem.h"

bool DynamicItem::is_handler_started = false;
std::vector<DynamicItem::HandleItemType> DynamicItem::handle_items;


void DynamicItem::add_item(GraphicItem* item, unsigned int delay) {
  DynamicItem::HandleItemType handle_item;
  handle_item.item = &*item;
  handle_item.delay = delay;
  handle_item.timer = NULL;
  DynamicItem::handle_items.push_back(handle_item);
}

void DynamicItem::remove_item(int id) {
  if (id >= 0 && id < handle_items.size()) { // Проверяем, что индекс в пределах вектора
    handle_items.erase(handle_items.begin() + id); 
  }
}

void DynamicItem::Handler() {
  if (is_handler_started) {
    for (int i = 0; i < handle_items.size(); ++i) {
      if (handle_items[i].timer != NULL) {
        if (xTimerIsTimerActive(handle_items[i].timer)) {
          // Обработка каждого таймера
          xTimerReset(handle_items[i].timer, 0);
          handle_items[i].item->animate(); // Вызов метода animate() каждого динамического объекта
        }
      }
    }
  }
}

void callback(TimerHandle_t xTimer) {
  int index = (int)pvTimerGetTimerID(xTimer);
  tftMutex.lock();
  ((TriangleGraphicItem*)DynamicItem::handle_items[index].item)->animate();
  tftMutex.unlock();
}

int DynamicItem::HandlerStart() {
  if (is_handler_started) {
    for (int i = 0; i < handle_items.size(); ++i) {
      if (handle_items[i].timer != NULL) {
        xTimerDelete(handle_items[i].timer, 0);
      }
    }
  }

  for (int i = 0; i < handle_items.size(); ++i) {
    TimerHandle_t timer = xTimerCreate(
        "itemTimer",
        pdMS_TO_TICKS(handle_items[i].delay),
        pdTRUE,
        (void*)i,
        callback
    );
    xTimerStart(timer, 0);
    handle_items[i].timer = timer;
  }
  is_handler_started = true;
  return 1;
}