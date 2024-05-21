#include "TFT_eSPI_HEADERS.h"
#include "Menu.h"
#include "DynamicItem.h"
#include "TriangleGraphicItem.h"
#include "SwitchItem.h"
#include "CONFIG.h"

TFT_eSPI tft = TFT_eSPI(320, 240); 
std::mutex tftMutex;

#define BTN_PIN_DOWN 22
#define BTN_PIN_UP 21
#define BTN_PIN_SEL 27
#define BTN_PIN_BACK 26

void ItemRender(int i) {
  switch (Menu::curent_menu->items_v[i]->GetItemType()) {
    case SwitchItem_Type:
        // Приведение типа к SwitchItem и вызов метода render()
        ((SwitchItem*)Menu::curent_menu->items_v[i])->render();
        break;
    default:
        Menu::curent_menu->items_v[i]->render();
        break;
  }
}

void ItemErase(int i) {
  switch (Menu::curent_menu->items_v[i]->GetItemType()) {
    case SwitchItem_Type:
        // Приведение типа к SwitchItem и вызов метода erase()
        ((SwitchItem*)Menu::curent_menu->items_v[i])->erase();
        ((SwitchItem*)Menu::curent_menu->items_v[i])->render();
        break;

    default:
        Menu::curent_menu->items_v[i]->erase();
        break;
  }
}

void TurnWhiteAction() {
  FONT_COLOR = 0x000;
  SCREEN_COLOR = 0xffffff;
  Menu::curent_menu->init_menu_render();
}
void TurnBlackAction() {
  FONT_COLOR = 0xffffff;
  SCREEN_COLOR = 0x000;
  Menu::curent_menu->init_menu_render();
}
void SwitchAction(SwitchItem* item) {
  item->erase();
  item->selectedItem = item->items[++item->selectedIndex];
  if (item->selectedIndex + 1 >=item->items.size()) item->selectedIndex = -1;
  // ... do something
  item->render();
  tft.setTextColor(FONT_SELECTED_COLOR);
  tft.print(" <");
  tft.setTextColor(FONT_COLOR);
}

void SwitchColor(SwitchItem* item) {
  item->erase();
  item->selectedItem = item->items[++item->selectedIndex];
  if (item->selectedIndex + 1 >=item->items.size()) item->selectedIndex = -1;
  switch (item->selectedIndex) {
    case 0:
      FONT_SELECTED_COLOR = tft.color565(0, 0, 255);
      break;
    case 1:
      FONT_SELECTED_COLOR = tft.color565(0, 255, 0);
      break;
    case -1:
      FONT_SELECTED_COLOR = tft.color565(255, 0, 100);
      break;
  }
  item->render();
  tft.setTextColor(FONT_SELECTED_COLOR);
  tft.print(" <");
  tft.setTextColor(FONT_COLOR);
}

void SpawnTrianRandom() {
  TriangleGraphicItem* triangle = new TriangleGraphicItem(rand()%tft.width(),tft.height()-rand() % (tft.height()/2), (rand()+20)%50, 0, 0, Menu::curent_menu, &TRIANGLE_COLOR_2);
  DynamicItem::add_item(triangle, 100);
  DynamicItem::HandlerStart();
}

void setup() {
  digitalWrite(TFT_CS, LOW);
  Serial.begin(115200);
  pinMode(BTN_PIN_UP, INPUT_PULLUP);
  pinMode(BTN_PIN_DOWN, INPUT_PULLUP);
  pinMode(BTN_PIN_SEL, INPUT_PULLUP);
  pinMode(BTN_PIN_BACK, INPUT_PULLUP);

  tft.begin();
  tft.setRotation(3);

  Menu* main_menu = new Menu("Main menu");
  MenuItem* main_menu_i1 = new MenuItem("Test 1");
  Menu* main_menu_i2 = new Menu("Goto menu 2");
  MenuItem* main_menu_i3 = new MenuItem("Test 3");
  MenuItem* main_menu_i4 = new MenuItem("Test 4");
  MenuItem* main_menu_i5 = new MenuItem("Turn White");
  MenuItem* main_menu_i6 = new MenuItem("Turn Black");
  main_menu->add_item(main_menu_i1);
  main_menu->add_item(main_menu_i2);
  main_menu->add_item(main_menu_i3);
  main_menu->add_item(main_menu_i4);
  main_menu->add_item(main_menu_i5);
  main_menu->add_item(main_menu_i6);
  main_menu_i5->action = TurnWhiteAction;
  main_menu_i6->action = TurnBlackAction;

  Menu::curent_menu = main_menu;
  
  MenuItem* main_menu2_i1 = new MenuItem("Menu2 item1");
  MenuItem* main_menu2_i2 = new MenuItem("Menu2 item2");
  SwitchItem* main_menu2_i3 = new SwitchItem("Switchme");
  main_menu_i2->add_item(main_menu2_i1);  
  main_menu_i2->add_item(main_menu2_i2);  
  main_menu_i2->add_item(main_menu2_i3);  

  SwitchItem::Item* switch_item1 =new SwitchItem::Item;
  switch_item1->name = "a";
  switch_item1->value = 0;
  main_menu2_i3->add_item(switch_item1);
  SwitchItem::Item* switch_item2 =new SwitchItem::Item;
  switch_item2->name = "b";
  switch_item2->value = 1;
  main_menu2_i3->add_item(switch_item2);
  main_menu2_i3->action = &SwitchAction;

  Menu* action_menu = new Menu("Action menu");
  SwitchItem* action_menu_i1 = new SwitchItem("'<'");
  action_menu_i1->action = &SwitchColor;

  SwitchItem::Item* action_menu_i1_item1 =new SwitchItem::Item;
  action_menu_i1_item1->name = "red";
  action_menu_i1_item1->value = 1;
  action_menu_i1->add_item(action_menu_i1_item1);
  SwitchItem::Item* action_menu_i1_item2 =new SwitchItem::Item;
  action_menu_i1_item2->name = "green";
  action_menu_i1_item2->value = 2;
  action_menu_i1->add_item(action_menu_i1_item2);
  SwitchItem::Item* action_menu_i1_item3 =new SwitchItem::Item;
  action_menu_i1_item3->name = "purple";
  action_menu_i1_item3->value = 3;
  action_menu_i1->add_item(action_menu_i1_item3);

  main_menu_i2->add_item(action_menu);

  MenuItem* action_menu_i2 = new MenuItem("Spawn trian");
  action_menu_i2->action = SpawnTrianRandom;
  action_menu->add_item(action_menu_i1);
  action_menu->add_item(action_menu_i2);
  Menu::curent_menu->init_menu_render();
  

  TriangleGraphicItem* triangle1 = new TriangleGraphicItem(tft.width()/2, tft.height()-50, 50, 0, 0, main_menu_i2, &TRIANGLE_COLOR_1);
  TriangleGraphicItem* triangle2 = new TriangleGraphicItem(tft.width()/2, tft.height()-70, 60, 0, 0, main_menu_i2, &TRIANGLE_COLOR_2);
  TriangleGraphicItem* triangle3 = new TriangleGraphicItem(tft.width()/2, tft.height()-90, 70, 0, 0, main_menu_i2, &TRIANGLE_COLOR_3);
  DynamicItem::add_item(triangle1, 100); 
  DynamicItem::add_item(triangle2, 80); 
  DynamicItem::add_item(triangle3, 70); 
  DynamicItem::HandlerStart();
}

void loop() {
  tftMutex.lock();
  if (digitalRead(BTN_PIN_DOWN) == LOW) {
    Menu::curent_menu->cur_item++;
    if (Menu::curent_menu->cur_item == Menu::curent_menu->items_v.size()) Menu::curent_menu->cur_item = 0;
    tft.setTextColor(FONT_COLOR);
    tft.setCursor(0,17);
    tft.setTextSize(3);
    for (int i = 0; i < Menu::curent_menu->items_v.size(); i++) {
      if (i == Menu::curent_menu->cur_item) {
        if (i > 0) ItemErase(i-1);
        else if (i == 0) ItemErase(Menu::curent_menu->items_v.size()-1);
        tft.setCursor(Menu::curent_menu->items_v[i]->Position.x,Menu::curent_menu->items_v[i]->Position.y);
        ItemRender(i);
        tft.setTextColor(FONT_SELECTED_COLOR);
        tft.println(" <");
        tft.setTextColor(FONT_COLOR);
      }
    }
    Serial.println("down_btn");
  }
  if (digitalRead(BTN_PIN_UP) == LOW) {
    Menu::curent_menu->cur_item--;
    if (Menu::curent_menu->cur_item < 0) Menu::curent_menu->cur_item = Menu::curent_menu->items_v.size()-1;
    tft.setTextColor(FONT_COLOR);
    tft.setCursor(0,17);
    tft.setTextSize(3);
    for (int i = 0; i < Menu::curent_menu->items_v.size(); i++) {
      if (i == Menu::curent_menu->cur_item) {
        if (i < Menu::curent_menu->items_v.size()-1) ItemErase(i+1);
        else if (i == Menu::curent_menu->items_v.size()-1) ItemErase(0);
        tft.setCursor(Menu::curent_menu->items_v[i]->Position.x,Menu::curent_menu->items_v[i]->Position.y);
        ItemRender(i);
        tft.setTextColor(FONT_SELECTED_COLOR);
        tft.println(" <");
        tft.setTextColor(FONT_COLOR);
      }
    }
    Serial.println("up_btn");
  }
  if (digitalRead(BTN_PIN_SEL) == LOW) {
    if (Menu::curent_menu->items_v[Menu::curent_menu->cur_item]->GetItemType() == 1) ((Menu*)Menu::curent_menu->items_v[Menu::curent_menu->cur_item])->action();// menu type
    else if (Menu::curent_menu->items_v[Menu::curent_menu->cur_item]->GetItemType() == 2) ((SwitchItem*)Menu::curent_menu->items_v[Menu::curent_menu->cur_item])->action(((SwitchItem*)Menu::curent_menu->items_v[Menu::curent_menu->cur_item]));// menu type
    else if (Menu::curent_menu->items_v[Menu::curent_menu->cur_item]->action != nullptr) Menu::curent_menu->items_v[Menu::curent_menu->cur_item]->action();
    Serial.print("sel_btn: ");
    Serial.println(Menu::curent_menu->items_v[Menu::curent_menu->cur_item]->name);
  }
  if (digitalRead(BTN_PIN_BACK) == LOW) {
    if (Menu::curent_menu->parent != nullptr) Menu::curent_menu->back_action();// menu type
    Serial.println("back_btn");
  }
  tftMutex.unlock();
  delay(100);
}