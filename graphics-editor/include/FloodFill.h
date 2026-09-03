#ifndef FLOODFILL_H
#define FLOODFILL_H

#include <stack>

#include <Color.h>
#include <Context.h>
#include <Pixel.h>
#include <Point.h>

class FloodFill : protected Pixel
{
    public:
        static void floodFill(int x,int y, Color color);

    protected:

    private:
        static void floodFill(int x,int y, Uint32 newColor, Uint32 oldColor, int width, int height);
};

#endif // FLOODFILL_H
