#ifndef BEZIER_H
#define BEZIER_H
#include <Point.h>
#include <Color.h>
#include <Context.h>

class Bezier
{
    public:
        Bezier();
        Bezier(Point p0, Point p1, Point p2, Point p3, Color color);
        void setPixel(int x, int y, int r, int g, int b);
        virtual ~Bezier();
        void draw();

    protected:

    private:
        Point p0, p1, p2, p3;
        Color color;
        void setPixel(int x, int y, int r, int g, int b, int a);
        void setPixel(int x, int y, Color color);
        void setPixel(int x, int y, Uint32 cor);
};

#endif // BEZIER_H
