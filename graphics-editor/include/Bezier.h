#ifndef BEZIER_H
#define BEZIER_H
#include <Point.h>
#include <Color.h>
#include <Context.h>
#include <Shape.h>

class Bezier : public Shape
{
    public:
        Bezier();
        Bezier(Point p0, Point p1, Point p2, Point p3, Color color);
        virtual ~Bezier();
        void draw();
        void translate(double tx, double ty);

    protected:

    private:
        Point p0, p1, p2, p3;
        Color color;
};

#endif // BEZIER_H
