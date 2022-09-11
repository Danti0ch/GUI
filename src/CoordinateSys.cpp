#include "drawer.h"
#include <assert.h>
#include <math.h>
#include <iostream>

static const double EPS = 1e-10;

CoordinateSus::CoordinateSus(uint x_lower_pixel,   uint x_upper_pixel, uint y_lower_pixel, uint y_upper_pixel,
                             double x_lower_lim, double x_upper_lim, double y_lower_lim, double y_upper_lim):
    x_lower_lim_(x_lower_lim),     x_upper_lim_(x_upper_lim),
    y_lower_lim_(y_lower_lim),     y_upper_lim_(y_upper_lim),
    x_lower_pixel_(x_lower_pixel), x_upper_pixel_(x_upper_pixel),
    y_lower_pixel_(y_lower_pixel), y_upper_pixel_(y_upper_pixel)
{
    assert(x_upper_pixel > x_lower_pixel);
    assert(y_lower_pixel > y_upper_pixel);
    assert(x_upper_lim - x_lower_lim > EPS);
    assert(y_upper_lim - y_lower_lim > EPS);

    scale_x_ = ((double)(x_upper_pixel - x_lower_pixel)) / (x_upper_lim - x_lower_lim);
    scale_y_ = ((double)(y_lower_pixel - y_upper_pixel)) / (y_upper_lim - y_lower_lim);

    step_val_ = (x_upper_lim - x_lower_lim) / ((double)(x_upper_pixel - x_lower_pixel));
}
//----------------------------------------------------------------------------------------//

int CoordinateSus::CountPixelPosX(double x_ct){

    int x_pixel_pos = round(x_ct * scale_x_) + x_lower_pixel_ + round((-x_lower_lim_) * scale_x_);

    return x_pixel_pos;
}
//----------------------------------------------------------------------------------------//

int CoordinateSus::CountPixelPosY(double y_ct){

    int y_pixel_pos = y_lower_pixel_ - round(-(y_lower_lim_ * scale_y_)) - round(y_ct * scale_y_);

    return y_pixel_pos;
}
//----------------------------------------------------------------------------------------//

int CoordinateSus::CountPixelPosX(Point pt){

    return CountPixelPosX(pt.GetX());
}
//----------------------------------------------------------------------------------------//

int CoordinateSus::CountPixelPosY(Point pt){

    return CountPixelPosY(pt.GetY());
}
//----------------------------------------------------------------------------------------//
