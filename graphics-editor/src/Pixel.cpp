#include "Pixel.h"

Pixel::Pixel() {

}

Pixel::~Pixel() {

}

void Pixel::setPixel(int x, int y, Uint32 color) {
    Color c = Color();
    Uint8 r = c.getColorComponent(color, 'r');
    Uint8 g = c.getColorComponent(color, 'g');
    Uint8 b = c.getColorComponent(color, 'b');
    Pixel::setPixel(x, y, r, g, b);
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

Uint32 Pixel::getPixel(int x, int y)
{
    SDL_Surface * window_surface = Context::getInstance()->getWindowSurface();

    int bpp = window_surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *) window_surface->pixels + y * window_surface->pitch + x * bpp;

    switch (bpp)
    {
        case 1:
            return *p;
            break;

        case 2:
            return *(Uint16 *)p;
            break;

        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
            break;

            case 4:
                return *(Uint32 *)p;
                break;

            default:
                return 0;       /* shouldn't happen, but avoids warnings */
      }
}
