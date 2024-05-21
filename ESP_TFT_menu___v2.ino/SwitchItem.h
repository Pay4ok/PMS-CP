#pragma once
#include "MenuItem.h"
#include <vector>

class SwitchItem :
    public MenuItem
{
public:
    struct Item {
        const char* name;
        int value;
    };
    typedef void (*ActionFunc)(SwitchItem*);
    ActionFunc action;
    Item* selectedItem;
    int selectedIndex;
    std::vector<Item*> items;

    void erase();
    void render();
    void add_item(Item* item);
    SwitchItem(const char* name);
    SwitchItem(const char* name, MenuItem* parent);
    SwitchItem(const char* name, MenuItem* parent, MenuItem* child);
    SwitchItem(const char* name, MenuItem* parent, void* action);
};

