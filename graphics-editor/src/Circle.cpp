#include "Circle.h"

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
