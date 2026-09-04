#ifndef CIRCLE_H
#define CIRCLE_H
#include <Point.h>
#include <Color.h>
#include <Context.h>
#include <Shape.h>

class Circle : public Shape
{
    public:
        Circle();
        Circle(Point center, int radius, Color color);
        virtual ~Circle();
        void draw();
        void translate(double tx, double ty);

    protected:

    private:
        Point center;
        int radius;
        Color color;
        void displayBresenhamCircle(int xc, int yc, int x, int y);
};

#endif // CIRCLE_H
