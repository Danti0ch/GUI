#ifndef PIXEL_H
#define PIXEL_H

#include "Color.h"

class Pixel{
public:

    Pixel(uint x, uint y, const Color& col):
        x_(x), y_(y), col_(col) {}

    uint x() const { return x_; } 
    uint y() const { return y_; } 

    uint& x() { return x_; } 
    uint& y() { return y_; } 

    const Color& col() const { return col_; }
private:
    uint x_, y_;
    Color col_;
};

#endif // PIXEL_H
