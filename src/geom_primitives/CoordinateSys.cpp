#include "GeometryObjects.h"
#include <assert.h>
#include <math.h>

using namespace geom;

//static const uint   COORD_SUS_GRID_SIZE = 30;
static const uint   N_COORD_SUS_GRIDS = 8;

static const uint ARROW_AXIS_PROJ_LEN = 5;

CoordinateSus::CoordinateSus(uint x_lower_pixel,   uint x_upper_pixel, uint y_lower_pixel, uint y_upper_pixel,
                             double x_lower_lim, double x_upper_lim, double y_lower_lim, double y_upper_lim):
    x_lower_lim_(x_lower_lim),     x_upper_lim_(x_upper_lim),
    y_lower_lim_(y_lower_lim),     y_upper_lim_(y_upper_lim),
    x_lower_pixel_(x_lower_pixel), x_upper_pixel_(x_upper_pixel),
    y_lower_pixel_(y_lower_pixel), y_upper_pixel_(y_upper_pixel)
{
    assert(x_upper_pixel > x_lower_pixel);
    assert(y_upper_pixel > y_lower_pixel);
    assert(x_upper_lim - x_lower_lim > geom::EPS);
    assert(y_upper_lim - y_lower_lim > geom::EPS);
    
    scale_x_ = ((double)(x_upper_pixel - x_lower_pixel)) / (x_upper_lim - x_lower_lim);
    scale_y_ = ((double)(y_upper_pixel - y_lower_pixel)) / (y_upper_lim - y_lower_lim);

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

    int y_pixel_pos = round(y_ct * scale_y_) + y_lower_pixel_ + n_y_lower_axis_pixels_;

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

    assert(y_pixel >= y_lower_pixel_ && y_pixel <= y_upper_pixel_);
    
    double val = (y_pixel - y_lower_pixel_ - n_y_lower_axis_pixels_) / scale_y_;

    return val;
}
//----------------------------------------------------------------------------------------//
int CheckCoordInCTS(const CoordinateSus& cts, uint x, uint y){

    if(x < cts.x_upper_pixel() && x > cts.x_lower_pixel() &&
       y < cts.y_upper_pixel() && y > cts.y_lower_pixel()){
        return 1;
    }
    return 0;
}
//----------------------------------------------------------------------------------------//
