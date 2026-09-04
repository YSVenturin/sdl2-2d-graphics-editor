#include "Point.h"

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

    // 1) Aplicar uma translação do ponto escolhido até a origem
    p_aux.translate(-origin.getX(), -origin.getY());

    // 2) Aplicar a escala
    p_aux.setX(p_aux.getX() * ex);
    p_aux.setY(p_aux.getY() * ey);

    //3) Transladá-lo até sua posição inicial
    p_aux.translate(origin.getX(), origin.getY());

    this->x = p_aux.getX();
    this->y = p_aux.getY();
}

