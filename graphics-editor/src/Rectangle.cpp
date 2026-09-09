#include "Rectangle.h"
#include <algorithm>

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

    if (this->selected) {
        Shape::drawHandle(topLeft);
        Shape::drawHandle(topRight);
        Shape::drawHandle(bottomLeft);
        Shape::drawHandle(bottomRight);
    }
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

void Rectangle::rotate(Point origin, double angleDegrees) {
    topLeft.rotate(origin, angleDegrees);
    topRight.rotate(origin, angleDegrees);
    bottomLeft.rotate(origin, angleDegrees);
    bottomRight.rotate(origin, angleDegrees);
}

double Rectangle::distanceTo(Point p) {
    double d1 = Shape::distancePointToSegment(p, topLeft, topRight);
    double d2 = Shape::distancePointToSegment(p, topRight, bottomRight);
    double d3 = Shape::distancePointToSegment(p, bottomRight, bottomLeft);
    double d4 = Shape::distancePointToSegment(p, bottomLeft, topLeft);

    return std::min(std::min(d1, d2), std::min(d3, d4));
}