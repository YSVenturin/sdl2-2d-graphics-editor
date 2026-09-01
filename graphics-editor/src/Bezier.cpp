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

void Bezier::setPixel(int x, int y, Uint32 cor) {

    Color c = Color();
    Uint8 r = c.getColorComponent(cor, 'r');
    Uint8 g = c.getColorComponent(cor, 'g');
    Uint8 b = c.getColorComponent(cor, 'b');
    this->setPixel(x, y, r, g, b);
}

void Bezier::setPixel(int x, int y, Color color) {
	this->setPixel(x, y, color.getR(),color.getG(),color.getB());
}

void Bezier::setPixel(int x, int y, int r, int g, int b) {
    setPixel(x, y, r, g, b, 255);
}

void Bezier::setPixel(int x, int y, int r, int g, int b, int a) {
    unsigned int * pixels;
    SDL_Surface * window_surface = Context::getInstance()->getWindowSurface();
    pixels = (unsigned int *) window_surface->pixels;
    pixels[x + y * window_surface->w] = SDL_MapRGBA(window_surface->format, r, g, b, a);
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
        setPixel(xu, yu, this->color);
    }
}
