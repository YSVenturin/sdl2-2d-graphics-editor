#include "ShapeList.h"

ShapeList::ShapeList() {

}

ShapeList::~ShapeList() {

}

void ShapeList::add(std::unique_ptr<Shape> shape) {
    this->shapes.push_back(std::move(shape));
}

void ShapeList::drawAll() {
    for (const auto& s : this->shapes) {
        s->draw();
    }
}

void ShapeList::remove(Shape* shape) {
    this->shapes.remove_if([shape](const std::unique_ptr<Shape>& s) {
        return s.get() == shape;
    });
}

void ShapeList::removeAll() {
    (this->shapes).clear();
}

Shape* ShapeList::findTop(Point p, double tolerance) {
    for (auto it = this->shapes.rbegin(); it != this->shapes.rend(); ++it) {
        if ((*it)->hitTest(p, tolerance)) {
            return it->get();
        }
    }
    return nullptr;
}