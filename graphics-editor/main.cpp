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
#include <Polygon.h>
#include <Shape.h>
#include <ShapeList.h>
#include <FloodFill.h>

using namespace std;

// SDL
unsigned int * pixels;
int width, height;
SDL_Surface * window_surface;
SDL_Renderer * renderer;

std::string title = "Graphics Editor";

void display(ShapeList &shapeList) {
    shapeList.drawAll();
    Color green(0, 255, 0);
    //FloodFill::floodFill(width/2, height/2, green);
}

int main() {
    setlocale(LC_ALL, NULL);

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * window = SDL_CreateWindow(title.c_str(),
                                           SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                           1024, 768,
                                           0);

    window_surface = SDL_GetWindowSurface(window);

    Context* context = Context::getInstance();
    context->setWindowSurface(window_surface);

    pixels = (unsigned int *) window_surface->pixels;
    width = window_surface->w;
    height = window_surface->h;

    ShapeList shapeList = ShapeList();

    Color red(255, 0, 0);
    Color blue(0, 0, 255);
    Color lightBlue(56, 204, 209);
    Color green(0, 255, 0);
    Color white(255, 255, 255);
    Color yellow(255, 255, 0);

    Point p0(100, 400);
    Point p1(150, 50);
    Point p2(490, 50);
    Point p3(540, 400);
    Point p4(width/2, height/2);

    Point p5(width/2-20, height/2-20);
    Point p6(width/2+20, height/2+20);
    Point p7(0, 0);

    std::list<Point> poly;
    poly.push_back(p0);
    poly.push_back(p1);
    poly.push_back(p2);
    poly.push_back(p3);
    poly.push_back(p5);

    Bezier b = Bezier(p0, p1, p2, p3, red);
    Bezier b2 = Bezier(p0, p1, p2, p3, white);
    Bezier b3 = Bezier(p0, p1, p2, p3, yellow);
    b.translate(100, 0);
    b3.scale(p0, 0.5, 0.5);

    Line l = Line(p5, p6, white);
    Line l2 = Line(p5, p6, white);
    Line l3 = Line(p5, p6, yellow);
    l.translate(-50, -50);
    l2.translate(0, 100);
    l3.translate(0, 100);
    l3.scale(p5, 2, 1);

    Rectangle r1 = Rectangle(p5, p6, red);
    Rectangle r2 = Rectangle(p5, p6, red);
    Rectangle r3 = Rectangle(p5, p6, red);
    r1.translate(-50, -50);
    r2.translate(0, 100);
    r3.scale(p5, 2, 2);

    Circle c = Circle (p0, 50, green);
    Circle c2 = Circle (p0, 50, white);
    Circle c3 = Circle (p0, 50, yellow);
    c2.translate(50, 50);
    c3.scale(p0, 0.5, 0.5);

    Polygon poly1 = Polygon(poly, blue);
    Polygon poly2 = Polygon(poly, white);
    Polygon poly3 = Polygon(poly, lightBlue);
    poly2.translate(50, 50);
    poly3.scale(p0, 0.5, 0.5);

    shapeList.add(std::make_unique<Line>(l));
    shapeList.add(std::make_unique<Line>(l2));
    shapeList.add(std::make_unique<Line>(l3));
    shapeList.add(std::make_unique<Rectangle>(r1));
    shapeList.add(std::make_unique<Rectangle>(r2));
    shapeList.add(std::make_unique<Rectangle>(r3));
    shapeList.add(std::make_unique<Bezier>(b));
    shapeList.add(std::make_unique<Bezier>(b2));
    shapeList.add(std::make_unique<Bezier>(b3));
    shapeList.add(std::make_unique<Circle>(c));
    shapeList.add(std::make_unique<Circle>(c2));
    shapeList.add(std::make_unique<Circle>(c3));
    shapeList.add(std::make_unique<Polygon>(poly1));
    shapeList.add(std::make_unique<Polygon>(poly2));
    shapeList.add(std::make_unique<Polygon>(poly3));

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
