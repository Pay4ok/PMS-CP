#include "TFT_eSPI_HEADERS.h"
#include "Menu.h"
#include "CONFIG.h"
#include "SwitchItem.h"
void ItemRender(int i);
void Menu::add_item(MenuItem *item) {
  item->parent = this;
  items_v.push_back(item);
}
Menu* Menu::curent_menu = nullptr;

void Menu::render() {
  Position.Init(0, tft.getCursorY());
  tft.print(name);
}

void Menu::action() {
  Menu::curent_menu = (Menu*)(Menu::curent_menu->items_v[Menu::curent_menu->cur_item]);
  Menu::curent_menu->init_menu_render();
}

void Menu::back_action() {
  Menu::curent_menu = (Menu*)(Menu::curent_menu->parent);
  Menu::curent_menu->init_menu_render();
}

void Menu::init_menu_render() {
  is_init = true;

  tft.fillScreen(SCREEN_COLOR);
  tft.setCursor(3,0);
  tft.setTextSize(2);
  tft.setTextColor(SCREEN_COLOR);
  tft.fillRect(0,0, 320, 14, tft.color565(105, 6, 6));
  tft.println(name);

  tft.setTextColor(FONT_COLOR);
  tft.setCursor(0,17);
  tft.setTextSize(3);
  for (int i = 0; i < items_v.size(); i++) {
    if (i == cur_item) {
      ItemRender(i);
      tft.setTextColor(FONT_SELECTED_COLOR);
      tft.println(" <");  
      tft.setTextColor(FONT_COLOR);
    }
    else {ItemRender(i); tft.println();}
  }
}
Menu::Menu(const char *n) : MenuItem(n) {
	this->itemType = Menu_Type;
	this->cur_item = 0;
  this->parent = nullptr;
}
Menu::Menu(const char* n, MenuItem* parent) : MenuItem(n, parent) {
	this->itemType = Menu_Type;
	this->cur_item = 0;
  this->parent = parent;
}
Menu::Menu(const char* n, MenuItem* parent, std::vector<MenuItem*> childs) : MenuItem(n, parent) {
	this->itemType = Menu_Type;
	this->cur_item = 0;
	this->items_v = childs;
  this->parent = parent;
}
Menu::Menu(const char* n, MenuItem* parent, void* action) : MenuItem(n, parent, action) {
	this->itemType = Menu_Type;
	this->cur_item = 0;
  this->parent = parent;
}