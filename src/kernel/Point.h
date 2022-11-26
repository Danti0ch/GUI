#ifndef POINT_H
#define POINT_H

#include <stdlib.h>

class Point{
public:
    Point(uint x, uint y):
        x_(x), y_(y){}

    uint x() const { return x_; }
    uint y() const { return y_; }
private:
    uint x_, y_;
};

#endif // POINT_H
