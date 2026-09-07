#include "ToolBox.h"
#include "Line.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Bezier.h"
#include "Polygon.h"
#include "Point.h"
#include <SDL2/SDL.h>
#include <algorithm>
#include <cmath>
#include <list>

namespace {
    const int BUTTON_WIDTH_OFFSET = 20;
    const int BUTTON_HEIGHT = 40;
    const int TOOL_Y_START = 10;
    const int TOOL_Y_STEP = 50;
    const int PALETTE_START_Y = 390;
    const int PALETTE_SIZE = 22;
    const int PALETTE_GAP = 26;
    const int ACTION_Y_UNDO = 500;
    const int ACTION_Y_DELETE = 550;
    const int ACTION_Y_SAVE = 600;
    const int SEPARATOR_Y = 370;
    const int CURRENT_COLOR_Y = 455;
    const int CURRENT_COLOR_HEIGHT = 30;
}

ToolBox::ToolBox(int width, int height) {
    this->width = width;
    this->height = height;

    currentTool = Tool::SELECT;
    currentColor = Color(0, 0, 0);

    colors.push_back(Color(0, 0, 0));       // preto
    colors.push_back(Color(255, 255, 255)); // branco
    colors.push_back(Color(255, 0, 0));     // vermelho
    colors.push_back(Color(0, 255, 0));     // verde
    colors.push_back(Color(0, 0, 255));     // azul
    colors.push_back(Color(255, 255, 0));   // amarelo
    colors.push_back(Color(255, 0, 255));   // magenta
    colors.push_back(Color(0, 255, 255));   // ciano
}

int ToolBox::toolY(Tool tool) const {
    switch (tool) {
        case Tool::SELECT:      return TOOL_Y_START + 0 * TOOL_Y_STEP;
        case Tool::LINE:        return TOOL_Y_START + 1 * TOOL_Y_STEP;
        case Tool::RECTANGLE:   return TOOL_Y_START + 2 * TOOL_Y_STEP;
        case Tool::CIRCLE:      return TOOL_Y_START + 3 * TOOL_Y_STEP;
        case Tool::BEZIER:      return TOOL_Y_START + 4 * TOOL_Y_STEP;
        case Tool::POLYGON:     return TOOL_Y_START + 5 * TOOL_Y_STEP;
        case Tool::FLOOD_FILL:  return TOOL_Y_START + 6 * TOOL_Y_STEP;
    }
    return 0;
}

bool ToolBox::contains(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

Tool ToolBox::getTool() const {
    return currentTool;
}

Color ToolBox::getColor() const {
    return currentColor;
}

ToolBox::Action ToolBox::getAction(int x, int y) const {
    if (x < 10 || x > width - 10)
        return Action::NONE;
    if (y >= ACTION_Y_UNDO && y < ACTION_Y_UNDO + BUTTON_HEIGHT)
        return Action::UNDO;
    if (y >= ACTION_Y_DELETE && y < ACTION_Y_DELETE + BUTTON_HEIGHT)
        return Action::DELETE;
    if (y >= ACTION_Y_SAVE && y < ACTION_Y_SAVE + BUTTON_HEIGHT)
        return Action::SAVE;
    return Action::NONE;
}

void ToolBox::handleClick(int x, int y) {
    if (!contains(x, y))
        return;

    // Pegar ferramentas
    if (x >= 10 && x <= width - 10) {
        if (y >= TOOL_Y_START && y < TOOL_Y_START + BUTTON_HEIGHT)
            currentTool = Tool::SELECT;
        else if (y >= TOOL_Y_START + TOOL_Y_STEP && y < TOOL_Y_START + TOOL_Y_STEP + BUTTON_HEIGHT)
            currentTool = Tool::LINE;
        else if (y >= TOOL_Y_START + 2 * TOOL_Y_STEP && y < TOOL_Y_START + 2 * TOOL_Y_STEP + BUTTON_HEIGHT)
            currentTool = Tool::RECTANGLE;
        else if (y >= TOOL_Y_START + 3 * TOOL_Y_STEP && y < TOOL_Y_START + 3 * TOOL_Y_STEP + BUTTON_HEIGHT)
            currentTool = Tool::CIRCLE;
        else if (y >= TOOL_Y_START + 4 * TOOL_Y_STEP && y < TOOL_Y_START + 4 * TOOL_Y_STEP + BUTTON_HEIGHT)
            currentTool = Tool::BEZIER;
        else if (y >= TOOL_Y_START + 5 * TOOL_Y_STEP && y < TOOL_Y_START + 5 * TOOL_Y_STEP + BUTTON_HEIGHT)
            currentTool = Tool::POLYGON;
        else if (y >= TOOL_Y_START + 6 * TOOL_Y_STEP && y < TOOL_Y_START + 6 * TOOL_Y_STEP + BUTTON_HEIGHT)
            currentTool = Tool::FLOOD_FILL;
    }

    // Pegar cor na paleta
    const int startX = 12;
    for (int i = 0; i < (int)colors.size(); i++) {
        int row = i / 4;
        int col = i % 4;
        int px = startX + col * PALETTE_GAP;
        int py = PALETTE_START_Y + row * PALETTE_GAP;
        if (x >= px && x <= px + PALETTE_SIZE && y >= py && y <= py + PALETTE_SIZE) {
            currentColor = colors[i];
            return;
        }
    }
}

void ToolBox::drawButton(SDL_Surface* surface, int y, bool selected) {
    Uint32 bg = SDL_MapRGB(surface->format,
                           selected ? 180 : 245,
                           selected ? 205 : 245,
                           selected ? 255 : 245);
    SDL_Rect rect = {10, y, width - BUTTON_WIDTH_OFFSET, BUTTON_HEIGHT};
    SDL_FillRect(surface, &rect, bg);

    Point p1(10, y);
    Point p2(width - 10, y + BUTTON_HEIGHT);
    Color border(90, 90, 90);
    Rectangle borda(p1, p2, border);
    borda.draw();
}

void ToolBox::drawToolIcon(SDL_Surface* surface, Tool tool, int y) {
    int cx = width / 2;
    int cy = y + BUTTON_HEIGHT / 2;
    Color black(20, 20, 20);

    switch (tool) {
        case Tool::SELECT: { // poderia ter desenhado com Polygon, se quiser deixar mais bonito boa sorte

            Point p1(cx - 10, cy - 13);
            Point p2(cx - 10, cy + 13);
            Point p3(cx + 9, cy + 5);
            Point p4(cx, cy + 10);
            Point p5(cx + 4, cy + 18);

            Line l1(p1, p2, black); l1.draw();
            Line l2(p2, p3, black); l2.draw();
            Line l3(p1, p3, black); l3.draw();
            Line l4(p4, p5, black); l4.draw();
            break;
        }
        case Tool::LINE: {
            Point p1(cx - 15, cy + 12);
            Point p2(cx + 15, cy - 12);
            Line linha(p1, p2, black);
            linha.draw();
            break;
        }
        case Tool::RECTANGLE: {
            Point p1(cx - 15, cy - 11);
            Point p2(cx + 15, cy + 11);
            Rectangle ret(p1, p2, black);
            ret.draw();
            break;
        }
        case Tool::CIRCLE: {
            Point centro(cx, cy);
            Circle circ(centro, 14, black);
            circ.draw();
            break;
        }
        case Tool::BEZIER: {
            Point p0(cx - 15, cy + 5);
            Point p1(cx - 15, cy - 12);
            Point p2(cx + 15, cy - 12);
            Point p3(cx + 15, cy + 5);

            Bezier curva(p0, p1, p2, p3, black);
            curva.draw();

            // pivos
            Circle c1(p1, 2, black); c1.draw();
            Circle c2(p2, 2, black); c2.draw();
            break;
        }
        case Tool::POLYGON: {
            std::list<Point> pts;

            pts.push_back(Point(cx, cy - 14));
            pts.push_back(Point(cx + 13, cy - 4));
            pts.push_back(Point(cx + 8,  cy + 11));
            pts.push_back(Point(cx - 8,  cy + 11));
            pts.push_back(Point(cx - 13, cy - 4));

            Polygon poly(pts, black);
            poly.draw();
            break;
        }
        case Tool::FLOOD_FILL: { // sla, pra mim parece um balde kkkk

            Point p1(cx - 12, cy - 5);
            Point p2(cx + 12, cy + 13);
            Rectangle balde(p1, p2, black);
            balde.draw();

            Point p3(cx - 10, cy - 5);
            Point p4(cx - 1, cy - 13);
            Rectangle topo(p3, p4, black);
            topo.draw();
            break;
        }
    }
}

void ToolBox::drawActionIcon(SDL_Surface* surface, int y, int action) {
    int cx = width / 2;
    int cy = y + BUTTON_HEIGHT / 2;
    Color black(20, 20, 20);

    if (action == 0) { // UNDO (lembrar de pegar ctrl + z no main tbm)
        Point p1(cx + 13, cy);
        Point p2(cx - 10, cy);
        Point p3(cx - 2, cy - 8);
        Point p4(cx - 2, cy + 8);
        Line l1(p1, p2, black); l1.draw();
        Line l2(p2, p3, black); l2.draw();
        Line l3(p2, p4, black); l3.draw();
    }
    else if (action == 1) { // DELETE (+ del no main?)
        Point p1(cx - 9, cy - 7);
        Point p2(cx + 9, cy + 12);
        Rectangle corpo(p1, p2, black);
        corpo.draw();

        Line tampa(Point(cx - 13, cy - 11), Point(cx + 13, cy - 11), black);
        tampa.draw();

        Line alca(Point(cx - 5, cy - 14), Point(cx + 5, cy - 14), black);
        alca.draw();
    }
    else if (action == 2) { // SAVE
        Point p1(cx - 13, cy - 14);
        Point p2(cx + 13, cy + 14);
        Rectangle disco(p1, p2, black);
        disco.draw();

        Point p3(cx - 7, cy - 11);
        Point p4(cx + 7, cy - 3);
        Rectangle etiq1(p3, p4, black);
        etiq1.draw();

        Point p5(cx - 7, cy + 4);
        Point p6(cx + 7, cy + 11);
        Rectangle etiq2(p5, p6, black);
        etiq2.draw();
    }
}

void ToolBox::drawPalette(SDL_Surface* surface) {
    const int startX = 12;

    for (int i = 0; i < (int)colors.size(); i++) {
        int row = i / 4;
        int col = i % 4;
        int x = startX + col * PALETTE_GAP;
        int y = PALETTE_START_Y + row * PALETTE_GAP;

        Uint32 color = SDL_MapRGB(surface->format,
                                  colors[i].getR(),
                                  colors[i].getG(),
                                  colors[i].getB());

        SDL_Rect rect = {x, y, PALETTE_SIZE, PALETTE_SIZE};
        SDL_FillRect(surface, &rect, color);

        Point p1(x, y);
        Point p2(x + PALETTE_SIZE, y + PALETTE_SIZE);
        Color border(60, 60, 60);
        Rectangle borda(p1, p2, border);
        borda.draw();
        
        // Destacar cor selecionada
        if (colors[i].getR() == currentColor.getR() &&
            colors[i].getG() == currentColor.getG() &&
            colors[i].getB() == currentColor.getB()) {
            Point s1(x - 2, y - 2);
            Point s2(x + PALETTE_SIZE + 2, y + PALETTE_SIZE + 2);
            Color sel(0, 0, 0);
            Rectangle selecao(s1, s2, sel);
            selecao.draw();
        }
    }

    Uint32 current = SDL_MapRGB(surface->format,
                                currentColor.getR(),
                                currentColor.getG(),
                                currentColor.getB());
    SDL_Rect rect = {12, CURRENT_COLOR_Y, width - 24, CURRENT_COLOR_HEIGHT};
    SDL_FillRect(surface, &rect, current);

    Point p1(12, CURRENT_COLOR_Y);
    Point p2(width - 12, CURRENT_COLOR_Y + CURRENT_COLOR_HEIGHT);
    Color border(60, 60, 60);
    Rectangle borda(p1, p2, border);
    borda.draw();
}

void ToolBox::draw(SDL_Surface* surface) {
    Uint32 bg = SDL_MapRGB(surface->format, 215, 215, 215);
    SDL_Rect rect = {0, 0, width, height};
    SDL_FillRect(surface, &rect, bg);

    Tool tools[] = {
        Tool::SELECT, Tool::LINE, Tool::RECTANGLE,
        Tool::CIRCLE, Tool::BEZIER, Tool::POLYGON,
        Tool::FLOOD_FILL
    };
    for (int i = 0; i < 7; i++) {
        int y = toolY(tools[i]);
        drawButton(surface, y, currentTool == tools[i]);
        drawToolIcon(surface, tools[i], y);
    }

    Color sep(120, 120, 120);
    Point p1(10, SEPARATOR_Y);
    Point p2(width - 10, SEPARATOR_Y);
    Line separador(p1, p2, sep);
    separador.draw();

    drawButton(surface, ACTION_Y_UNDO, false);
    drawActionIcon(surface, ACTION_Y_UNDO, 0);
    drawButton(surface, ACTION_Y_DELETE, false);
    drawActionIcon(surface, ACTION_Y_DELETE, 1);
    drawButton(surface, ACTION_Y_SAVE, false);
    drawActionIcon(surface, ACTION_Y_SAVE, 2);

    // Paleta
    drawPalette(surface);
}