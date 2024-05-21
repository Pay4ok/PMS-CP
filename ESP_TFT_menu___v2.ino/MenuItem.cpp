#include "TFT_eSPI_HEADERS.h"
#include "MenuItem.h"
#include "Menu.h"
#include "CONFIG.h"

int MenuItem::GetItemType() { return itemType; }

void MenuItem::render() {
  Position.Init(tft.getCursorX(), tft.getCursorY());
  tft.setCursor(Position.x, Position.y);
  tft.print(name);
}

void MenuItem::erase() {
  tft.setTextColor(SCREEN_COLOR);
  tft.setCursor(Position.x, Position.y);
  tft.print(name);
  tft.print(" <");
  tft.setTextColor(FONT_COLOR);
  tft.setCursor(Position.x, Position.y);
  tft.println(name);
}

MenuItem::MenuItem(const char* name) {
	this->name = name;
	this->parent = nullptr;
	this->child = nullptr;
	this->action = nullptr;
}

MenuItem::MenuItem(const char* name, MenuItem* parent) {
	this->name = name;
	this->parent = parent;
	this->child = nullptr;
	this->action = nullptr;
	((Menu*)parent)->items_v.push_back(this);
}

MenuItem::MenuItem(const char* name, MenuItem* parent, MenuItem* child) {
	this->name = name;
	this->parent = parent;
	this->action = nullptr;
	this->child = child;
	((Menu*)parent)->items_v.push_back(this);
}

MenuItem::MenuItem(const char* name, MenuItem* parent, void* action) {
	this->name = name;
	this->parent = (MenuItem*)parent;
	this->action = nullptr;
	this->child = nullptr;
	((Menu*)parent)->items_v.push_back(this);
}