#include "TFT_eSPI_HEADERS.h"
#include "TriangleGraphicItem.h"
#include "Menu.h"
#include "CONFIG.h"

TriangleGraphicItem::TriangleGraphicItem(int x, int y, int s, int w, int h, Menu* parent, int* color) 
    : GraphicItem(w, h), centerX(x), centerY(y), size(s), angle(0) {
      this->parent = parent;
      this->color = color;
      x1_t = 0; x2_t = 0; x3_t = 0;
      y1_t = 0; y2_t = 0; y3_t = 0;  
      points.resize(size * size);
      animate(); // При создании объекта сразу рисуем треугольник
}

void TriangleGraphicItem::draw() {
    clear(); // Очищаем экран перед рисованием
    // Определяем координаты вершин треугольника
    int x1 = centerX + size * cos(angle);
    int y1 = centerY + size * sin(angle);

    int x2 = centerX + size * cos(angle + 2 * M_PI / 3);
    int y2 = centerY + size * sin(angle + 2 * M_PI / 3);

    int x3 = centerX + size * cos(angle + 4 * M_PI / 3);
    int y3 = centerY + size * sin(angle + 4 * M_PI / 3);

    if (!(x1_t == 0 && y1_t == 0 && x2_t == 0 && y2_t == 0 && x3_t == 0 && y3_t == 0)) {
      tft.drawLine(x1_t, y1_t, x2_t, y2_t, SCREEN_COLOR);
      tft.drawLine(x2_t, y2_t, x3_t, y3_t, SCREEN_COLOR);
      tft.drawLine(x3_t, y3_t, x1_t, y1_t, SCREEN_COLOR);
    }
    
    x1_t = x1; x2_t = x2; x3_t = x3;
    y1_t = y1; y2_t = y2; y3_t = y3;  
    // Рисуем треугольник на экране
    tft.drawLine(x1, y1, x2, y2, *color);
    tft.drawLine(x2, y2, x3, y3, *color);
    tft.drawLine(x3, y3, x1, y1, *color);
}

void TriangleGraphicItem::clear() {
    for (int i = 0; i < size * size; ++i) {
        points[i] = 0; // Очищаем все точки
    }
}

// Метод для вращения треугольника
void TriangleGraphicItem::animate() {
  if (Menu::curent_menu == this->parent) {
    angle += 0.1; // Изменяем угол для вращения
    draw(); // Перерисовываем треугольник
  }
}