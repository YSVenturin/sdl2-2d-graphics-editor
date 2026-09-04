#include "Polygon.h"
#include <iostream>

Polygon::Polygon() : Shape() {
}

Polygon::Polygon(std::list<Point> points, Color color) {
    this->color = color;
    this->points = points;
}

Polygon::~Polygon() {
}

void Polygon::draw() {
    if (this->points.empty()) {
        return;
    }

    for (auto it = (this->points).begin(); std::next(it) != (this->points).end(); it++) {
        Point p1 = *it;
        Point p2 = *std::next(it);
        Line(p1, p2, this->color).draw();
    }

    Point p1 = (this->points).back();
    Point p2 = (this->points).front();
    Line(p1, p2, this->color).draw();
}

void Polygon::translate(double tx, double ty) {
    for (auto& p : this->points) {
        p.translate(tx, ty);
    }
}
