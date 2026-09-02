#ifndef SHAPE_H
#define SHAPE_H

#include <Color.h>
#include <Context.h>

class Shape
{
    public:
        Shape();
        virtual ~Shape();
        virtual void draw() = 0;
        void setPixel(int x, int y, int r, int g, int b);
        Uint32 getPixel(int x, int y);

    protected:
        void setPixel(int x, int y, int r, int g, int b, int a);
        void setPixel(int x, int y, Uint32 color);
        void setPixel(int x, int y, Color color);

    private:
};

#endif // SHAPE_H
