#include "drawer.h"
#include <assert.h>
#include <math.h>
#include <iostream>

static const double EPS                 = 1e-10;
static const uint   COORD_SUS_GRID_SIZE = 30;

// TODO: fix left_lim < 0
// TODO: поиграться с расцветкой и толщиной осей и векторов

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

    n_x_upper_axis_pixels_ = trunc(x_upper_lim * scale_x_);
    n_x_lower_axis_pixels_ = trunc((-x_lower_lim) * scale_x_);
    n_y_upper_axis_pixels_ = trunc(y_upper_lim * scale_y_);
    n_y_lower_axis_pixels_ = trunc((-y_lower_lim) * scale_y_);

    step_val_ = (x_upper_lim - x_lower_lim) / ((double)(x_upper_pixel - x_lower_pixel));
}
//----------------------------------------------------------------------------------------//

int CoordinateSus::CountPixelPosX(double x_ct) const {

    int x_pixel_pos = round(x_ct * scale_x_) + x_lower_pixel_ + n_x_lower_axis_pixels_;

    return x_pixel_pos;
}
//----------------------------------------------------------------------------------------//

int CoordinateSus::CountPixelPosY(double y_ct) const {

    int y_pixel_pos = y_lower_pixel_ - n_y_lower_axis_pixels_ - round(y_ct * scale_y_);

    return y_pixel_pos;
}
//----------------------------------------------------------------------------------------//

double CoordinateSus::CountAxisPosX(int x_pixel) const {

    assert(x_pixel >= x_lower_pixel_ && x_pixel <= x_upper_pixel_);
    
    double val = (x_pixel - x_lower_pixel_ - n_x_lower_axis_pixels_) / scale_x_;

    return val;
}
//----------------------------------------------------------------------------------------//

double CoordinateSus::CountAxisPosY(int y_pixel) const {

    assert(y_pixel >= y_upper_pixel_ && y_pixel <= y_lower_pixel_);
    
    double val = (-y_pixel + y_lower_pixel_ - n_y_lower_axis_pixels_) / scale_y_;

    return val;
}
//----------------------------------------------------------------------------------------//

// TODO: make smarter разметка линий на координатной оси. Например умное деление на линии единичных отрезков вида 10^x
void CoordinateSus::Draw(gl::Window* window) const {

    assert(window != NULL);

    uint N_X_UPPER_AXIS_LINES  = n_x_upper_axis_pixels_ / COORD_SUS_GRID_SIZE;
    uint N_X_LOWER_AXIS_LINES  = n_x_lower_axis_pixels_ / COORD_SUS_GRID_SIZE;
    
    uint N_Y_UPPER_AXIS_LINES  = n_y_upper_axis_pixels_ / COORD_SUS_GRID_SIZE;
    uint N_Y_LOWER_AXIS_LINES  = n_y_lower_axis_pixels_ / COORD_SUS_GRID_SIZE;
    
    for(uint n_x_line = -N_X_LOWER_AXIS_LINES; n_x_line <= N_X_UPPER_AXIS_LINES; n_x_line++){
        
        int x_ct = (-n_x_line * COORD_SUS_GRID_SIZE) + n_x_lower_axis_pixels_ + x_lower_pixel_;

        gl::DrawLine(window, x_ct, y_lower_pixel_, x_ct, y_upper_pixel_);
    }

    for(uint n_y_line = -N_Y_LOWER_AXIS_LINES; n_y_line <= N_Y_UPPER_AXIS_LINES; n_y_line++){
        
        int y_ct = y_lower_pixel_ - n_y_lower_axis_pixels_ - n_y_line * COORD_SUS_GRID_SIZE;

        gl::DrawLine(window, x_lower_pixel_, y_ct, x_upper_pixel_, y_ct);
    }

    return;
}
//----------------------------------------------------------------------------------------//
