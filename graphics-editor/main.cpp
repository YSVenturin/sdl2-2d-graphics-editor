#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <stack>
#include <sstream>
#include <unistd.h>
#include <list>
#include <memory>

#include <Context.h>
#include <Color.h>
#include <Point.h>
#include <Line.h>
#include <Bezier.h>
#include <Circle.h>
#include <Rectangle.h>
#include <Shape.h>
#include <ShapeList.h>

using namespace std;

// SDL
unsigned int * pixels;
int width, height;
SDL_Surface * window_surface;
SDL_Renderer * renderer;

std::string title = "Graphics Editor";

void display(ShapeList &shapeList) {
    shapeList.drawAll();
}

int main() {
    setlocale(LC_ALL, NULL);

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * window = SDL_CreateWindow(title.c_str(),
                                           SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                           640, 480,
                                           SDL_WINDOW_RESIZABLE);

    window_surface = SDL_GetWindowSurface(window);

    Context* context = Context::getInstance();
    context->setWindowSurface(window_surface);

    pixels = (unsigned int *) window_surface->pixels;
    width = window_surface->w;
    height = window_surface->h;

    ShapeList shapeList = ShapeList();

    Color red(255, 0, 0);
    Color blue(0, 0, 255);

    Point p0(100, 400);
    Point p1(150, 50);
    Point p2(490, 50);
    Point p3(540, 400);
    Point p4(width/2, height/2);

    Point p5(width/2-20, height/2-20);
    Point p6(width/2+20, height/2+20);

    shapeList.add(std::make_unique<Circle>(p4, 100, red));
    shapeList.add(std::make_unique<Bezier>(p0, p1, p2, p3, red));
    shapeList.add(std::make_unique<Line>(p0, p3, red));
    shapeList.add(std::make_unique<Rectangle>(p5, p6, blue));

    while (1) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                exit(0);
            }
        }

        display(shapeList);

        SDL_UpdateWindowSurface(window);
    }
}
