#pragma once

enum ItemType {
	MenuItem_Type = 0,
	Menu_Type = 1,
	SwitchItem_Type = 2,
	GraphicItem_Type = 3,
};

class MenuItem {
protected:
	int itemType;
public:
	const char* name;
	MenuItem* parent;
	MenuItem* child;
  
	struct Position {
		int x, y;
		void Init(int x, int y) { this->x = x; this->y = y; };
	} Position;
  
  typedef void (*ActionFunc)();
  ActionFunc action;

	void render();
	void erase();
	int GetItemType();

	MenuItem(const char* name);
	MenuItem(const char* name, MenuItem* parent);
	MenuItem(const char* name, MenuItem* parent, MenuItem* child);
	MenuItem(const char* name, MenuItem* parent, void* action);
};
