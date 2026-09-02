#ifndef LINE_H
#define LINE_H
#include <Point.h>
#include <Color.h>
#include <Shape.h>

class Line : public Shape
{
    public:
        Line();
        Line(Point start, Point end, Color color);
        Line(Point start, Point end, Color color, int antialias);
        void draw();
        virtual ~Line();

    protected:

    private:
        Point start;
        Point end;
        Color color;
        int antialias = 0;
        void bresenham(int x1, int y1, int x2, int y2, int r, int g, int b);
        void drawWuLine(int x0, int y0, int x1, int y1, Color color);

};

#endif // LINE_H
