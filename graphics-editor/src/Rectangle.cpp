#include "Rectangle.h"

Rectangle::Rectangle() : Shape() {
}

Rectangle::Rectangle(Point topLeft, Point bottomRight, Color color) : Shape(){
    this->topLeft = topLeft;
    this->bottomRight = bottomRight;
    this->topRight = Point(bottomRight.getX(), topLeft.getY());
    this->bottomLeft = Point(topLeft.getX(), bottomRight.getY());
    this->color = color;
}

Rectangle::~Rectangle()
{
    //dtor
}

void Rectangle::draw() {
    Line(topLeft, topRight, color).draw();
    Line(topRight, bottomRight, color).draw();
    Line(bottomRight, bottomLeft, color).draw();
    Line(bottomLeft, topLeft, color).draw();
}

void Rectangle::translate(double tx, double ty) {
    this->topLeft.translate(tx, ty);
    this->topRight.translate(tx, ty);
    this->bottomLeft.translate(tx, ty);
    this->bottomRight.translate(tx, ty);
}

void Rectangle::scale(Point origin, double ex, double ey) {
    topLeft.scale(origin, ex, ey);
    topRight.scale(origin, ex, ey);
    bottomLeft.scale(origin, ex, ey);
    bottomRight.scale(origin, ex, ey);
}
