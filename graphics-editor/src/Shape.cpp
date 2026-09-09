#include "Shape.h"
#include <cmath>

Shape::Shape() {
    this->selected = false;
}

Shape::~Shape() {

}

bool Shape::hitTest(Point p, double tolerance) {
    return this->distanceTo(p) <= tolerance;
}

void Shape::setSelected(bool value) {
    this->selected = value;
}

bool Shape::isSelected() const {
    return this->selected;
}

// Pra saber se um clique caiu "em cima"
// https://randygaul.github.io/math/collision-detection/2014/07/01/Distance-Point-to-Line-Segment.html
double Shape::distancePointToSegment(Point p, Point a, Point b) {
    double px = p.getX();
    double py = p.getY();
    double ax = a.getX();
    double ay = a.getY();
    double bx = b.getX();
    double by = b.getY();

    double dx = bx - ax;
    double dy = by - ay;

    double lengthSquared = dx * dx + dy * dy;

    double t;
    if (lengthSquared == 0.0) {
        // a e b sao o mesmo ponto
        t = 0.0;
    } else {
        t = ((px - ax) * dx + (py - ay) * dy) / lengthSquared;
        if (t < 0.0) t = 0.0;
        if (t > 1.0) t = 1.0;
    }

    double closestX = ax + t * dx;
    double closestY = ay + t * dy;

    double diffX = px - closestX;
    double diffY = py - closestY;

    return std::sqrt(diffX * diffX + diffY * diffY);
}

void Shape::drawHandle(Point p) {
    int x = (int) p.getX();
    int y = (int) p.getY();

    // Laranja pra destaque? Caixa preta é laranja!
    Color highlight(255, 140, 0);

    for (int dx = -3; dx <= 3; dx++) {
        for (int dy = -3; dy <= 3; dy++) {
            Shape::setPixel(x + dx, y + dy, highlight);
        }
    }
}