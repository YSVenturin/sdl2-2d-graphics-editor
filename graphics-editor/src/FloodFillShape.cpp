#include "FloodFillShape.h"
#include "FloodFill.h"

FloodFillShape::FloodFillShape() : Shape() {

}

FloodFillShape::FloodFillShape(Point seed, Color color) : Shape() {
    this->seed = seed;
    this->color = color;
}

FloodFillShape::~FloodFillShape() {

}

void FloodFillShape::draw() {
    FloodFill::floodFill((int) this->seed.getX(), (int) this->seed.getY(), this->color);
}

void FloodFillShape::translate(double tx, double ty) {
    
}

void FloodFillShape::scale(Point origin, double ex, double ey) {

}

void FloodFillShape::rotate(Point origin, double angleDegrees) {

}

double FloodFillShape::distanceTo(Point p) {
    return Point::distance(this->seed, p);
}
