#include "SwitchItem.h"
#include "Menu.h"
#include "CONFIG.h"
#include "TFT_eSPI_HEADERS.h"

void SwitchItem::render() {
  Position.Init(tft.getCursorX(), tft.getCursorY());
  tft.setCursor(0, Position.y);
  tft.print(name);
  tft.print(" ");
  tft.setTextColor(FONT_SWITCHITEM_COLOR);
  tft.print(selectedItem->name);
  tft.setTextColor(FONT_COLOR);
}

void SwitchItem::add_item(Item *item) {
  items.push_back(item);
  if (selectedItem == nullptr) {selectedItem = item; selectedIndex = 0;}
}

void SwitchItem::erase() {
  tft.setTextColor(SCREEN_COLOR);
  tft.setCursor(0, Position.y);
  tft.print(name);
  tft.print(" ");
  tft.print(selectedItem->name);
  tft.print(" <");
  tft.setTextColor(FONT_COLOR);
}

SwitchItem::SwitchItem(const char* n) : MenuItem(n) {
	this->itemType = SwitchItem_Type;
  selectedItem = nullptr;
  action = nullptr;
}
SwitchItem::SwitchItem(const char* n, MenuItem* parent) : MenuItem(n, parent) {
	this->itemType = SwitchItem_Type;
}
SwitchItem::SwitchItem(const char* n, MenuItem* parent, MenuItem* child) : MenuItem(n, parent, child) {
	this->itemType = SwitchItem_Type;
}
SwitchItem::SwitchItem(const char* n, MenuItem* parent, void* action) : MenuItem(n, parent, action) {
	this->itemType = SwitchItem_Type;
}