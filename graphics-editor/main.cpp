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

std::unique_ptr<Shape> createShape(Tool tool, Color color, int x1, int y1, int x2, int y2) {
    Point p1(x1, y1);
    Point p2(x2, y2);
    switch(tool) {
        case Tool::LINE: return std::make_unique<Line>(p1, p2, color);
        case Tool::RECTANGLE: return std::make_unique<Rectangle>(p1, p2, color);
        case Tool::CIRCLE: {
            int radius = (int)std::sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
            return std::make_unique<Circle>(p1, radius, color);
        }
        default: return nullptr;
    }
}

// criar Bezier com um ponto de controle (P1 = P2 = control, tipo o Paint)
std::unique_ptr<Shape> createBezier(Point p0, Point p3, Point control, Color color) {
    Point p1 = control;
    Point p2 = control;
    return std::make_unique<Bezier>(p0, p1, p2, p3, color);
}

void finishPolygon(ShapeList& list, std::list<Point>& points, Color color) {
    if (points.size() < 3) {
        printf("Poligono precisa de pelo menos 3 pontos.\n");
        return;
    }
    list.add(std::make_unique<Polygon>(points, color));
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
    //shapeList.drawAll();
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

    // Variáveis para Bezier
    bool bezierWaitingP0 = false;
    bool bezierWaitingP3 = false;
    Point bezierP0;
    Point bezierP3;
    Point bezierControl;

    // Variáveis para Poligono
    std::list<Point> polygonPoints;
    bool polygonDrawing = false;
    std::unique_ptr<Line> polygonTempLine = nullptr;
    Point polygonTempPoint; // ultimo ponto do mouse?

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

                // fazer do ctrl + z, pensando bem, isso aqui vai ser complicado, ele apenas vai desfazer a figura?
                    // se incluir o esquema de desfazer transformação ai fica complexo...

                // fazer do del

                // Adicionar botao de acao para limpar a tela? limpar lista de Shapes?
                    // mais um motivo para FloodFill ser um Shape?

                //acho que só, pq ja temos a toolbox
            }

            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                int mx = event.button.x;
                int my = event.button.y;

                // clicou na toolbox?
                if (toolbox.contains(mx, my)) {
                    toolbox.handleClick(mx, my);

                    if (polygonDrawing) {
                        finishPolygon(shapeList, polygonPoints, toolbox.getColor());
                        polygonDrawing = false;
                        polygonPoints.clear();
                        polygonTempLine = nullptr;
                    }

                    bezierWaitingP0 = false;
                    bezierWaitingP3 = false;
                    tempShape = nullptr;
                } else {

                    Tool tool = toolbox.getTool();
                    Color color = toolbox.getColor();

                    switch (tool) {
                        case Tool::FLOOD_FILL:
                            //shapeList.add(std::make_unique<FloodFillShape>(Point(mx, my), color));
                                // teria que ter algo assim? FloodFill tbm precisa herdar de shape para manter as alterações? que?
                            //printf("Color: %d\n", color.getColor());
                            // nao inicia desenho
                            //SDL_UpdateWindowSurface(window); ???? testar depois...
                            break;

                        case Tool::POLYGON:
                            if (!polygonDrawing) {
                                polygonDrawing = true;
                                polygonPoints.clear();
                                polygonPoints.push_back(Point(mx, my));
                            } else {
                                Point first = polygonPoints.front();
                                double dist = std::sqrt((mx - first.getX())*(mx - first.getX()) + (my - first.getY())*(my - first.getY()));
                                if (dist <= 5.0) {
                                    finishPolygon(shapeList, polygonPoints, color);
                                    polygonDrawing = false;
                                    polygonPoints.clear();
                                    polygonTempLine = nullptr;
                                } else {
                                    polygonPoints.push_back(Point(mx, my));
                                }
                            }
                            break;

                        case Tool::BEZIER:
                            if (!bezierWaitingP0) {
                                // primeiro clique: define P0
                                bezierP0 = Point(mx, my);
                                bezierWaitingP0 = true;
                                bezierWaitingP3 = false;
                                //printf("P0 definido (%d, %d)\n", mx, my);
                            } else if (!bezierWaitingP3) {
                                // segundo clique: define P3
                                bezierP3 = Point(mx, my);
                                bezierWaitingP3 = true;

                                bezierControl.setX((bezierP0.getX() + bezierP3.getX()) / 2);
                                bezierControl.setY((bezierP0.getY() + bezierP3.getY()) / 2);
                                tempShape = createBezier(bezierP0, bezierP3, bezierControl, color);
                                //printf("arraste para controlar\n");
                            } else {
                                // sla?
                            }
                            break;

                        default:
                            // LINE, RECTANGLE, CIRCLE: iniciar arraste normal
                            startX = mx;
                            startY = my;
                            endX = mx;
                            endY = my;
                            drawing = true;
                            tempShape = nullptr;
                            break;
                    }
                }
            }

            if (event.type == SDL_MOUSEMOTION) {
                int mx = event.motion.x;
                int my = event.motion.y;

                // Se estiver desenhando com arraste (LINE, RECT, CIRCLE, BEZIER (inicio?))
                if (drawing && !polygonDrawing && !bezierWaitingP3) {
                    endX = mx;
                    endY = my;
                    Tool tool = toolbox.getTool();
                    Color color = toolbox.getColor();
                    tempShape = createShape(tool, color, startX, startY, endX, endY);
                }

                if (polygonDrawing && !polygonPoints.empty()) {
                    Point last = polygonPoints.back();
                    polygonTempLine = std::make_unique<Line>(last, Point(mx, my), toolbox.getColor());
                }

                if (bezierWaitingP3) {
                    bezierControl = Point(mx, my);
                    Color color = toolbox.getColor();
                    tempShape = createBezier(bezierP0, bezierP3, bezierControl, color);
                }

                // linha reta temporaria de P0 ate o mouse para a primeira parte do Bezier
                if (bezierWaitingP0 && !bezierWaitingP3) {
                    tempShape = std::make_unique<Line>(bezierP0, Point(mx, my), toolbox.getColor());
                }
            }

            if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
                // Finaliza arraste para LINE, RECT, CIRCLE
                if (drawing && !polygonDrawing && !bezierWaitingP3) {
                    endX = event.button.x;
                    endY = event.button.y;
                    Tool tool = toolbox.getTool();
                    Color color = toolbox.getColor();
                    auto newShape = createShape(tool, color, startX, startY, endX, endY);
                    if (newShape) {
                        shapeList.add(std::move(newShape));
                    }
                    drawing = false;
                    tempShape = nullptr;
                }

                // Finaliza Bezier
                if (bezierWaitingP3) {
                    Color color = toolbox.getColor();
                    auto newBezier = createBezier(bezierP0, bezierP3, bezierControl, color);
                    if (newBezier) {
                        shapeList.add(std::move(newBezier));
                    }
                    bezierWaitingP0 = false;
                    bezierWaitingP3 = false;
                    tempShape = nullptr;
                }
            }

            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT) {
                if (polygonDrawing) {
                    finishPolygon(shapeList, polygonPoints, toolbox.getColor());
                    polygonDrawing = false;
                    polygonPoints.clear();
                    polygonTempLine = nullptr;
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

        // Enquanto o poligono esta sendo desenhado, mantem visiveis os segmentos
        if (polygonDrawing && polygonPoints.size() >= 2) {
            Color color = toolbox.getColor();
            auto it = polygonPoints.begin();
            Point prev = *it;
            ++it;
            for (; it != polygonPoints.end(); ++it) {
                Line(prev, *it, color).draw();
                prev = *it;
            }
        }

        if (polygonTempLine) {
            polygonTempLine->draw();
        }

        toolbox.draw(window_surface);

        SDL_UpdateWindowSurface(window);
    }
}