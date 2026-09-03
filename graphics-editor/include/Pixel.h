#ifndef PIXEL_H
#define PIXEL_H

#include <Color.h>
#include <Context.h>

class Pixel
{
    public:
        Pixel();
        virtual ~Pixel();

    protected:
        static void setPixel(int x, int y, int r, int g, int b);
        static void setPixel(int x, int y, Color color);
        static void setPixel(int x, int y, Uint32 color);
        static void setPixel(int x, int y, int r, int g, int b, int a);
        static Uint32 getPixel(int x, int y);

    private:
};

#endif // PIXEL_H
