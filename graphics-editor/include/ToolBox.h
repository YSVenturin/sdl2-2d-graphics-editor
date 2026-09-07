#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <SDL2/SDL.h>
#include <vector>
#include <Color.h>

enum class Tool {
    SELECT,
    LINE,
    RECTANGLE,
    CIRCLE,
    BEZIER,
    POLYGON,
    FLOOD_FILL
};

class ToolBox {
private:
    int width;
    int height;

    Tool currentTool;
    Color currentColor;

    std::vector<Color> colors; // fazer esquema igual no Paint

    void drawButton(SDL_Surface* surface, int y, bool selected);
    void drawToolIcon(SDL_Surface* surface, Tool tool, int y);
    void drawActionIcon(SDL_Surface* surface, int y, int action);
    void drawPalette(SDL_Surface* surface);

    int toolY(Tool tool) const;

public:
    enum class Action { NONE, UNDO, DELETE, SAVE };

    ToolBox(int width, int height);


    void draw(SDL_Surface* surface); // deixar flexivel...
    bool contains(int x, int y) const; // Verifica se um ponto (x,y) está dentro da área da toolbox.
    void handleClick(int x, int y);

    Action getAction(int x, int y) const;
    Tool getTool() const;
    Color getColor() const;
};

#endif