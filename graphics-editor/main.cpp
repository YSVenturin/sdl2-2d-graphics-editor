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

#include <ToolBox.h>

#include <chrono>
#include <ctime>
#include <iomanip>

#ifdef _WIN32
    #include <direct.h>
    #define MKDIR(path) _mkdir(path)
#else
    #include <sys/stat.h>
    #define MKDIR(path) mkdir(path, 0755)
#endif // codigo original do exemplo do professor era pra Linux

using namespace std;

// Função para criar shape temporario, na movimenta do mouse pos click!
std::unique_ptr<Shape> createShape(Tool tool, Color color, int x1, int y1, int x2, int y2) {
    Point p1(x1, y1);
    Point p2(x2, y2);
    switch(tool) {
        case Tool::LINE: return std::make_unique<Line>(p1, p2, color);
        case Tool::RECTANGLE: return std::make_unique<Rectangle>(p1, p2, color);
        // Ai tem que viajar legal pra conseguir fazer os outros: CIRCLE, BEZIER, POLYGON, FLOOD_FILL (estes precisam de UMA lógica diferente...)
        default: return nullptr;
    }
}

long long generateSaveId() {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm localTime = *std::localtime(&currentTime);

    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y%m%d%H%M%S");

    return std::stoll(oss.str());
}

std::string getSaveDirectory() {
#ifdef _WIN32
    const char* home = getenv("USERPROFILE");
    std::string separator = "\\";
#else
    const char* home = getenv("HOME");
    std::string separator = "/";
#endif

    std::string base = (home != nullptr) ? std::string(home) : std::string(".");
    return base + separator + "Pictures";
}

void saveFile(SDL_Window* window) {
#ifdef _WIN32
    std::string separator = "\\";
#else
    std::string separator = "/";
#endif

    std::string dir = getSaveDirectory();
    MKDIR(dir.c_str());

    std::string name = dir + separator + "desenho-" + std::to_string(generateSaveId()) + ".bmp";

    SDL_Surface* surface = SDL_GetWindowSurface(window);

    if (SDL_SaveBMP(surface, name.c_str()) == 0) {
        printf("Arquivo salvo com sucesso: %s\n", name.c_str());
    }
    else {
        printf("Erro ao salvar: %s\n", SDL_GetError());
    }
}

// SDL
unsigned int * pixels;
int width, height;
SDL_Surface * window_surface;
SDL_Renderer * renderer;

std::string title = "Graphics Editor";

void display(ShapeList &shapeList) {
    shapeList.drawAll();
    //Color green(0, 255, 0);
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

    ToolBox toolbox(200, 768);

    // Variáveis de desenho
    bool drawing = false;
    int startX, startY;
    int endX, endY;
    std::unique_ptr<Shape> tempShape = nullptr;

    pixels = (unsigned int *) window_surface->pixels;
    width = window_surface->w;
    height = window_surface->h;

    ShapeList shapeList = ShapeList();

    // comentar depois...
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

            if (event.type == SDL_KEYDOWN) {

                SDL_Keycode key = event.key.keysym.sym;
                bool ctrl = (event.key.keysym.mod & KMOD_CTRL) != 0;

                if (ctrl && key == SDLK_s) {
                    saveFile(window);
                }

                // fazer do ctrl + z

                // fazer do del

                //acho que só, pq ja temos a toolbox
            }

            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                int mx = event.button.x;
                int my = event.button.y;

                // clicou na toolbox?
                if (toolbox.contains(mx, my)) {
                    toolbox.handleClick(mx, my);
                } else {
                    // Inicia desenho
                    startX = mx;
                    startY = my;
                    endX = mx;
                    endY = my;
                    drawing = true;
                    tempShape = nullptr; // criado durante o move
                }
            }

            if (event.type == SDL_MOUSEMOTION) {
                if (drawing) {
                    endX = event.motion.x;
                    endY = event.motion.y;

                    // Atualiza shape temp
                    Tool tool = toolbox.getTool();
                    Color color = toolbox.getColor();

                    // Cria shape temp
                    tempShape = createShape(tool, color, startX, startY, endX, endY);
                }
            }

            if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
                if (drawing) {
                    endX = event.button.x;
                    endY = event.button.y;

                    // Cria a shape final e adiciona ao ShapeList
                    Tool tool = toolbox.getTool();
                    Color color = toolbox.getColor();
                    auto newShape = createShape(tool, color, startX, startY, endX, endY);
                    if (newShape) {
                        shapeList.add(std::move(newShape));
                    }
                    drawing = false;
                    tempShape = nullptr;
                }
            }
        }

        SDL_FillRect(window_surface, NULL, Color::RGB(255, 255, 255));
        shapeList.drawAll();

        //display(); 
        /*
            pra mim só ficou mais dificil trabalhar com a função display pq fica precisando pssar os parametros e parece não fazer diferença
            nenhuma para o loop, então por hora vou jogar tudo aqui no main mesmo...
        */

        if (tempShape) {
            tempShape->draw();
        }

        toolbox.draw(window_surface);

        SDL_UpdateWindowSurface(window);
    }
}
