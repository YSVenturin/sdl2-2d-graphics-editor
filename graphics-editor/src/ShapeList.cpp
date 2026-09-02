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

void ShapeList::removeAll() {
    (this->shapes).clear();
}
