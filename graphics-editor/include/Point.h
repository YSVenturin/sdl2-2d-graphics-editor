#ifndef POINT_H
#define POINT_H


class Point
{
    public:
        Point();
        Point(double x, double y);
        double getX();
        double getY();
        void setX(double x);
        void setY(double y);
        virtual ~Point();
        void translate(double tx, double ty);

    protected:

    private:
        double x, y;
};

#endif // POINT_H
