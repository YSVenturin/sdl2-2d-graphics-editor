#ifndef FLOODFILLSHAPE_H
#define FLOODFILLSHAPE_H

#include <Point.h>
#include <Color.h>
#include <Shape.h>


class FloodFillShape : public Shape
{
    public:
        FloodFillShape();
        FloodFillShape(Point seed, Color color);
        virtual ~FloodFillShape();
        void draw();
        void translate(double tx, double ty);
        void scale(Point origin, double ex, double ey);
        void rotate(Point origin, double angleDegrees);
        double distanceTo(Point p);

    protected:

    private:
        Point seed;
        Color color;
};

#endif // FLOODFILLSHAPE_H
