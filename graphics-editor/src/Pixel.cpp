#include "Pixel.h"

Pixel::Pixel() {}
Pixel::~Pixel() {}

void Pixel::setPixel(int x, int y, Uint32 color) {
    SDL_Surface *window_surface = Context::getInstance()->getWindowSurface();
    if (!window_surface) return;
    int w = window_surface->w;
    int h = window_surface->h;
    if (x < 0 || x >= w || y < 0 || y >= h) return;
    unsigned int *pixels = (unsigned int *)window_surface->pixels;
    pixels[x + y * w] = color;
}

void Pixel::setPixel(int x, int y, Color color) {
    Pixel::setPixel(x, y, color.getR(), color.getG(), color.getB());
}

void Pixel::setPixel(int x, int y, int r, int g, int b) {
    setPixel(x, y, r, g, b, 255);
}

void Pixel::setPixel(int x, int y, int r, int g, int b, int a) {
    SDL_Surface *window_surface = Context::getInstance()->getWindowSurface();
    if (!window_surface) return;
    int w = window_surface->w;
    int h = window_surface->h;
    if (x < 0 || x >= w || y < 0 || y >= h) return;
    unsigned int *pixels = (unsigned int *)window_surface->pixels;
    pixels[x + y * w] = SDL_MapRGBA(window_surface->format, r, g, b, a);
}

Uint32 Pixel::getPixel(int x, int y) {
    SDL_Surface *window_surface = Context::getInstance()->getWindowSurface();
    if (!window_surface) return 0;
    int w = window_surface->w;
    int h = window_surface->h;
    if (x < 0 || x >= w || y < 0 || y >= h) return 0;
    unsigned int *pixels = (unsigned int *)window_surface->pixels;
    return pixels[x + y * w];
}