#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <stack>
#include <sstream>
#include <unistd.h>

#include <Context.h>
#include <Color.h>
#include <Point.h>
#include <Line.h>

using namespace std;

// SDL
unsigned int * pixels;
int width, height;
SDL_Surface * window_surface;
SDL_Renderer * renderer;

std::string title = "Graphics Editor";

void display() {
    Point start(100, 100);
    Point end(500, 300);
    Color red(255, 0, 0);

    Line line(start, end, red);
    line.draw();
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

    while (1) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                exit(0);
            }
        }

        display();

        SDL_UpdateWindowSurface(window);

        SDL_Delay(16);
    }
}
