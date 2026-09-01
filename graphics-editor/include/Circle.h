#ifndef CIRCLE_H
#define CIRCLE_H
#include <Point.h>
#include <Color.h>
#include <Context.h>

class Circle
{
    public:
        Circle();
        Circle(Point center, int radius, Color color);
        void setPixel(int x, int y, int r, int g, int b);
        virtual ~Circle();
        void draw();

    protected:

    private:
        Point center;
        int radius;
        Color color;
        void setPixel(int x, int y, int r, int g, int b, int a);
        void setPixel(int x, int y, Color color);
        void setPixel(int x, int y, Uint32 cor);
        void displayBresenhamCircle(int xc, int yc, int x, int y);
};

#endif // CIRCLE_H
