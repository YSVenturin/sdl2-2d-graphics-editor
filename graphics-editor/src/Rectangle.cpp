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
