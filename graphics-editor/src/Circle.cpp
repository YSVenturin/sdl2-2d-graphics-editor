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

void Circle::setPixel(int x, int y, Uint32 cor) {
    Color c = Color();
    Uint8 r = c.getColorComponent(cor, 'r');
    Uint8 g = c.getColorComponent(cor, 'g');
    Uint8 b = c.getColorComponent(cor, 'b');
    this->setPixel(x, y, r, g, b);
}

void Circle::setPixel(int x, int y, Color color) {
	this->setPixel(x, y, color.getR(),color.getG(),color.getB());
}

void Circle::setPixel(int x, int y, int r, int g, int b) {
    setPixel(x, y, r, g, b, 255);
}

void Circle::setPixel(int x, int y, int r, int g, int b, int a) {
    unsigned int * pixels;
    SDL_Surface * window_surface = Context::getInstance()->getWindowSurface();
    pixels = (unsigned int *) window_surface->pixels;
    pixels[x + y * window_surface->w] = SDL_MapRGBA(window_surface->format, r, g, b, a);
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
    setPixel(xc+x, yc+y, this->color);
    setPixel(xc-x, yc+y, this->color);
    setPixel(xc+x, yc-y, this->color);
    setPixel(xc-x, yc-y, this->color);
    setPixel(xc+y, yc+x, this->color);
    setPixel(xc-y, yc+x, this->color);
    setPixel(xc+y, yc-x, this->color);
    setPixel(xc-y, yc-x, this->color);
}
