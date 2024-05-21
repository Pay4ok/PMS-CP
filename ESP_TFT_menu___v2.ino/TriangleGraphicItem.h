#include "GraphicItem.h"
#include <vector>
#include <math.h>

class TriangleGraphicItem : public GraphicItem {
private:
    int centerX, centerY;
    int size;
    float angle;
    int* color;
    int x1_t, y1_t, x2_t, y2_t, x3_t, y3_t; // Координаты вершин треугольника
public:
    TriangleGraphicItem(int x, int y, int s, int w, int h, Menu* parent, int* color); // Конструктор
    void draw(); // Метод для рисования треугольника
    void clear(); // Метод для очистки экрана
    void animate(); // Метод для анимации
};
