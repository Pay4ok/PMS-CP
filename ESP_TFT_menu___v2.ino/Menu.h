#pragma once
#include "MenuItem.h"
#include <vector>

class MenuItem;

class Menu : public MenuItem {
public:
  static Menu* curent_menu;
	int cur_item;
	std::vector<MenuItem*> items_v;
  bool is_init = false;

  void add_item(MenuItem* item);
  void render();
  void action();
  void back_action();
  void init_menu_render();
	Menu(const char* name);
	Menu(const char* name, MenuItem* parent);
	Menu(const char* name, MenuItem* parent, std::vector<MenuItem*> childs);
	Menu(const char* name, MenuItem* parent, void* action);
};