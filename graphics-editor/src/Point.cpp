#include "Point.h"
#include <cmath>

Point::Point()
{
    //ctor
}

Point::Point(double x, double y)
{
    this->x = x;
    this->y = y;
}

Point::~Point()
{
    //dtor
}


double Point::getX()
{
    return this->x;
}

double Point::getY()
{
    return this->y;
}

void Point::setX(double x)
{
    this->x = x;
}

void Point::setY(double y)
{
    this->y = y;
}

void Point::translate(double tx, double ty) {
    this->x = this->x + tx;
    this->y = this->y + ty;
}

void Point::scale(Point origin, double ex, double ey) {
    // Ponto auxiliar para calculos
    Point p_aux = Point(this->x, this->y);

    // 1) Aplicar uma transla��o do ponto escolhido at� a origem
    p_aux.translate(-origin.getX(), -origin.getY());

    // 2) Aplicar a escala
    p_aux.setX(p_aux.getX() * ex);
    p_aux.setY(p_aux.getY() * ey);

    //3) Translad�-lo at� sua posi��o inicial
    p_aux.translate(origin.getX(), origin.getY());

    this->x = p_aux.getX();
    this->y = p_aux.getY();
}

void Point::rotate(Point origin, double angleDegrees) {

    Point p_aux = Point(this->x, this->y);

    p_aux.translate(-origin.getX(), -origin.getY());

    double rad = angleDegrees * M_PI / 180.0;
    double cosA = cos(rad);
    double sinA = sin(rad);

    double rx = p_aux.getX() * cosA - p_aux.getY() * sinA;
    double ry = p_aux.getX() * sinA + p_aux.getY() * cosA;

    p_aux.setX(rx);
    p_aux.setY(ry);

    p_aux.translate(origin.getX(), origin.getY());

    this->x = p_aux.getX();
    this->y = p_aux.getY();
}

double Point::distance(Point a, Point b) {
    double dx = a.getX() - b.getX();
    double dy = a.getY() - b.getY();
    return std::sqrt(dx * dx + dy * dy);
}