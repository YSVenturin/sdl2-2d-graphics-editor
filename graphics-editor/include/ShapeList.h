#ifndef SHAPELIST_H
#define SHAPELIST_H

#include <list>
#include <memory>

#include <Shape.h>

class ShapeList
{
    public:
        ShapeList();
        virtual ~ShapeList();
        void add(std::unique_ptr<Shape> shape);
        void drawAll();
        void remove(Shape* shape);
        void removeAll();

        // procura na lista o objeto correto
        Shape* findTop(Point p, double tolerance = 5.0);

    protected:

    private:
        std::list<std::unique_ptr<Shape>> shapes;
};

#endif // SHAPELIST_H
