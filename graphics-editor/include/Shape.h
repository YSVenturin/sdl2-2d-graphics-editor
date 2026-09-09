#ifndef SHAPE_H
#define SHAPE_H

#include <Pixel.h>
#include <Point.h>
#include <Color.h>

class Shape : protected Pixel {
    public:
        Shape();
        virtual ~Shape();
        virtual void draw() = 0;
        virtual void translate(double tx, double ty) = 0;
        virtual void scale(Point origin, double ex, double ey) = 0;
        virtual void rotate(Point origin, double angleDegrees) = 0;
        virtual double distanceTo(Point p) = 0;
        bool hitTest(Point p, double tolerance = 5.0);
        void setSelected(bool value);
        bool isSelected() const;

    protected:
        bool selected;
        static double distancePointToSegment(Point p, Point a, Point b);

        // uma especie de marcador visual??? na hora selecionar...
        static void drawHandle(Point p);

    private:
};

#endif // SHAPE_H
