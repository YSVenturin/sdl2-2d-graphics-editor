#include "FloodFill.h"

void FloodFill::floodFill(int x, int y, Color color, SDL_Surface* fills_surface) {
    SDL_Surface *window_surface = Context::getInstance()->getWindowSurface();
    int width = window_surface->w;
    int height = window_surface->h;

    if (y < 0 || y > height - 1 || x < 0 || x > width - 1) {
        return;
    }

    Uint32 oldColor = Pixel::getPixel(x, y);
    Uint32 newColor = color.getColor();

    if (oldColor == newColor) {
        return;
    }

    FloodFill::floodFill(x, y, newColor, oldColor, width, height, fills_surface);
}

void FloodFill::floodFill(int x,int y, Uint32 newColor, Uint32 oldColor, int width, int height, SDL_Surface* fills_surface) {
    std::stack<Point> st;
    st.push(Point(x, y));

    while (st.size() > 0) {
        Point p = st.top();
        st.pop();
        int x = static_cast<int>(p.getX()); // x e y sao double no Point, tem que fazer o cast
        int y = static_cast<int>(p.getY());

        if (y < 0 || y > height - 1 || x < 0 || x > width - 1) {
            continue;
        }

        if (Pixel::getPixel(x, y) == oldColor) {
            Pixel::setPixel(x, y, newColor);
            Pixel::setPixel(fills_surface, x, y, newColor);
            st.push(Point(x+1, y));
            st.push(Point(x-1, y));
            st.push(Point(x, y+1));
            st.push(Point(x, y-1));
        }
    }
}
