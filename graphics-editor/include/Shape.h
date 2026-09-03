#ifndef SHAPE_H
#define SHAPE_H

#include <Pixel.h>

class Shape : protected Pixel {
    public:
        Shape();
        virtual ~Shape();
        virtual void draw() = 0;

    protected:

    private:
};

#endif // SHAPE_H
