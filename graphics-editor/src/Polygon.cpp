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

    if (this->selected) {
        for (Point &v : this->points) {
            Shape::drawHandle(v);
        }
    }
}

void Polygon::addPoint(Point p) {
    this->points.push_back(p);
}

void Polygon::translate(double tx, double ty) {
    for (auto& p : this->points) {
        p.translate(tx, ty);
    }
}

void Polygon::scale(Point origin, double ex, double ey) {
    for (auto& p : this->points) {
        p.scale(origin, ex, ey);
    }
}

void Polygon::rotate(Point origin, double angleDegrees) {
    for (auto& p : this->points) {
        p.rotate(origin, angleDegrees);
    }
}

double Polygon::distanceTo(Point p) {
    if (this->points.empty()) {
        return 1e18;
    }

    double minDist = 1e18;

    for (auto it = this->points.begin(); std::next(it) != this->points.end(); it++) {
        double d = Shape::distancePointToSegment(p, *it, *std::next(it));
        if (d < minDist) minDist = d;
    }

    double dClose = Shape::distancePointToSegment(p, this->points.back(), this->points.front());
    if (dClose < minDist) minDist = dClose;

    return minDist;
}
