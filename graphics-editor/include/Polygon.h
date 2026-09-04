#ifndef POLYGON_H
#define POLYGON_H

#include <list>

#include <Point.h>
#include <Line.h>
#include <Color.h>
#include <Shape.h>

class Polygon : public Shape
{
    public:
        Polygon();
        Polygon(std::list<Point> points, Color color);
        virtual ~Polygon();
        void draw();
        void addPoint(Point p);
        void translate(double tx, double ty);

    protected:

    private:
        Color color;
        std::list<Point> points;
};

#endif // POLYGON_H
