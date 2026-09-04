#include "Bezier.h"
#include <cstdio>
#include <math.h>


Bezier::Bezier() : Shape()
{
    //ctor
}

Bezier::Bezier(Point p0, Point p1, Point p2, Point p3, Color color) : Shape() {
    this->p0 = p0;
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->color = color;
}

Bezier::~Bezier()
{
    //dtor
}

void Bezier::draw() {
    int xu, yu;
    float u;

    int x0 = p0.getX();
    int x1 = p1.getX();
    int x2 = p2.getX();
    int x3 = p3.getX();

    int y0 = p0.getY();
    int y1 = p1.getY();
    int y2 = p2.getY();
    int y3 = p3.getY();

    for (u=0; u <= 1; u+=0.0001) {
        xu = pow((1-u),3)*x0+3*u*pow((1-u),2)*x1+3*u*u*(1-u)*x2+pow(u,3)*x3;
        yu = pow((1-u),3)*y0+3*u*pow((1-u),2)*y1+3*u*u*(1-u)*y2+pow(u,3)*y3;
        Shape::setPixel(xu, yu, this->color);
    }
}

void Bezier::translate(double tx, double ty) {
    this->p0.translate(tx, ty);
    this->p1.translate(tx, ty);
    this->p2.translate(tx, ty);
    this->p3.translate(tx, ty);
}
