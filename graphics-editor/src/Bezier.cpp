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

    if (this->selected) {
        Shape::drawHandle(p0);
        Shape::drawHandle(p1);
        Shape::drawHandle(p2);
        Shape::drawHandle(p3);
    }
}

void Bezier::translate(double tx, double ty) {
    this->p0.translate(tx, ty);
    this->p1.translate(tx, ty);
    this->p2.translate(tx, ty);
    this->p3.translate(tx, ty);
}

void Bezier::scale(Point origin, double ex, double ey) {
    this->p0.scale(origin, ex, ey);
    this->p1.scale(origin, ex, ey);
    this->p2.scale(origin, ex, ey);
    this->p3.scale(origin, ex, ey);
}

void Bezier::rotate(Point origin, double angleDegrees) {
    this->p0.rotate(origin, angleDegrees);
    this->p1.rotate(origin, angleDegrees);
    this->p2.rotate(origin, angleDegrees);
    this->p3.rotate(origin, angleDegrees);
}

double Bezier::distanceTo(Point p) {
    // Nao achei uma formula simples para a distancia ate uma curva...
    // https://stackoverflow.com/questions/4272943/what-algorithm-determines-the-nearness-of-a-point-to-a-bezier-curve
    double x0 = p0.getX(), y0 = p0.getY();
    double x1 = p1.getX(), y1 = p1.getY();
    double x2 = p2.getX(), y2 = p2.getY();
    double x3 = p3.getX(), y3 = p3.getY();

    const int SEGMENTS = 100;
    Point prev = p0;
    double minDist = 1e18;

    for (int i = 1; i <= SEGMENTS; i++) {
        double u = (double) i / SEGMENTS;
        double mu = 1.0 - u;

        double bx = mu*mu*mu*x0 + 3*u*mu*mu*x1 + 3*u*u*mu*x2 + u*u*u*x3;
        double by = mu*mu*mu*y0 + 3*u*mu*mu*y1 + 3*u*u*mu*y2 + u*u*u*y3;

        Point curr(bx, by);
        double d = Shape::distancePointToSegment(p, prev, curr);
        if (d < minDist) minDist = d;
        prev = curr;
    }

    return minDist;
}
