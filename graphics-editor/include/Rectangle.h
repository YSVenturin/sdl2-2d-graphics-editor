#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <Point.h>
#include <Line.h>
#include <Color.h>
#include <Context.h>
#include <Shape.h>

class Rectangle : public Shape
{
    public:
        Rectangle();
        Rectangle(Point topLeft, Point bottomRight, Color color);
        virtual ~Rectangle();
        void draw();

    protected:

    private:
        Point topLeft;
        Point topRight;
        Point bottomLeft;
        Point bottomRight;
        Color color;
};

#endif // RECTANGLE_H
