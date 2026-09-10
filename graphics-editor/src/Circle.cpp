#include "Circle.h"
#include <cmath>

Circle::Circle() : Shape() {
}

Circle::Circle(Point center, int radius, Color color) : Shape(){
    this->center = center;
    this->radius = radius;
    this->color = color;
}

Circle::~Circle()
{
    //dtor
}

void Circle::draw() {
    int x = 0;
    int y = this->radius;
    int decesionParameter = 3 - 2 * this->radius;

    displayBresenhamCircle(this->center.getX(), this->center.getY(), x, y);

    while (y >= x)
    {
        x++;

        if (decesionParameter > 0)
        {
            y--;
            decesionParameter = decesionParameter + 4 * (x - y) + 10;
        }
        else
            decesionParameter = decesionParameter + 4 * x + 6;

        displayBresenhamCircle(this->center.getX(), this->center.getY(), x, y);
    }

    if (this->selected) {
        double cx = this->center.getX();
        double cy = this->center.getY();
        Shape::drawHandle(Point(cx, cy));
        Shape::drawHandle(Point(cx + this->radius, cy));
        Shape::drawHandle(Point(cx - this->radius, cy));
        Shape::drawHandle(Point(cx, cy + this->radius));
        Shape::drawHandle(Point(cx, cy - this->radius));
    }
}

void Circle::displayBresenhamCircle(int xc, int yc, int x, int y) {
    Shape::setPixel(xc+x, yc+y, this->color);
    Shape::setPixel(xc-x, yc+y, this->color);
    Shape::setPixel(xc+x, yc-y, this->color);
    Shape::setPixel(xc-x, yc-y, this->color);
    Shape::setPixel(xc+y, yc+x, this->color);
    Shape::setPixel(xc-y, yc+x, this->color);
    Shape::setPixel(xc+y, yc-x, this->color);
    Shape::setPixel(xc-y, yc-x, this->color);
}

void Circle::translate(double tx, double ty) {
    this->center.translate(tx, ty);
}

void Circle::scale(Point origin, double ex, double ey) {
    this->center.scale(origin, ex, ey);
    this->radius *= ex; // circle specific case, ex == ey
}

void Circle::rotate(Point origin, double angleDegrees) {
    this->center.rotate(origin, angleDegrees);
}

double Circle::distanceTo(Point p) {
    double d = Point::distance(this->center, p);
    return std::fabs(d - this->radius);
}