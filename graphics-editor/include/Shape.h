#ifndef SHAPE_H
#define SHAPE_H

#include <Pixel.h>
#include <Point.h>

class Shape : protected Pixel {
    public:
        Shape();
        virtual ~Shape();
        virtual void draw() = 0;
        virtual void translate(double tx, double ty) = 0;
        virtual void scale(Point origin, double ex, double ey) = 0;

    protected:

    private:
};

#endif // SHAPE_H
