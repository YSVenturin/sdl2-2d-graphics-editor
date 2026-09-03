#include "Pixel.h"

Pixel::Pixel() {

}

Pixel::~Pixel() {

}

void Pixel::setPixel(int x, int y, Uint32 color) {
    SDL_Surface *window_surface = Context::getInstance()->getWindowSurface();
    unsigned int *pixels = (unsigned int *)window_surface->pixels;
    pixels[x + y * window_surface->w] = color;
}

void Pixel::setPixel(int x, int y, Color color) {
	Pixel::setPixel(x, y, color.getR(),color.getG(),color.getB());
}

void Pixel::setPixel(int x, int y, int r, int g, int b) {
    setPixel(x, y, r, g, b, 255);
}

void Pixel::setPixel(int x, int y, int r, int g, int b, int a) {
    unsigned int * pixels;
    SDL_Surface * window_surface = Context::getInstance()->getWindowSurface();
    pixels = (unsigned int *) window_surface->pixels;
    pixels[x + y * window_surface->w] = SDL_MapRGBA(window_surface->format, r, g, b, a);
}

Uint32 Pixel::getPixel(int x, int y){
    unsigned int * pixels;
    SDL_Surface * window_surface = Context::getInstance()->getWindowSurface();
    pixels = (unsigned int *) window_surface->pixels;

    if((x >= 0 && x < window_surface->w) && (y >= 0 && y < window_surface->h))
        return pixels[x + window_surface->w * y];
    else
        return -1;
}
