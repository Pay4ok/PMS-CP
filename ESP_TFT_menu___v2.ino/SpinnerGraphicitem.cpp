#include "HardwareSerial.h"
#include "SpinnerGraphicitem.h"
#include "TFT_eSPI_HEADERS.h"

void SpinnerGraphicitem::clear() {
  for (int i = 0; i < points.size(); i++) {
    if (points[i] == 1) tft.drawPixel(i % width,i / width, 0x000);
  }
}

void SpinnerGraphicitem::draw() {
    for (int i = 0; i < points.size(); i++) {
        if (points[i] == 1 && i > 0) { // Проверяем, что точка включена и не является первой в массиве
            points[i - 1] = 1; // Включаем предыдущую точку
            points[i] = 0; // Выключаем текущую точку
            tft.drawPixel(i % width, i / width, 0x123123); // Рисуем текущую точку
        }
    }
}

void SpinnerGraphicitem::animate() {
  Serial.println("spinner animation");
  clear();
  draw();
}

SpinnerGraphicitem::SpinnerGraphicitem(int w, int h) : GraphicItem(w, h) {
}