#ifndef DRAWER_H
#define DRAWER_H

#include "graphic_lib_wrapper.h"
#include "geometry_objects.h"

typedef unsigned int uint;

namespace prim{

// TODO: RESTRUCT
class CoordinateSus{

private:
    
    double x_lower_lim_, x_upper_lim_;
    double y_lower_lim_, y_upper_lim_;

    int x_lower_pixel_, x_upper_pixel_;
    int y_lower_pixel_, y_upper_pixel_;

    int n_x_upper_axis_pixels_, n_x_lower_axis_pixels_;
    int n_y_upper_axis_pixels_, n_y_lower_axis_pixels_;
    
    double scale_x_, scale_y_;
    double step_val_;
public:
    
    CoordinateSus(uint x_lower_pixel, uint x_upper_pixel, uint y_upper_pixel, uint y_lower_pixel,
                  double x_lower_lim, double x_upper_lim, double y_lower_lim, double y_upper_lim);

    double x_lower_lim() const { return x_lower_lim_; }
    double x_upper_lim() const { return x_upper_lim_; }
    double y_lower_lim() const { return y_lower_lim_; }
    double y_upper_lim() const { return y_upper_lim_; }
    
    int x_lower_pixel() const { return x_lower_pixel_; }
    int x_upper_pixel() const { return x_upper_pixel_; }
    int y_lower_pixel() const { return y_lower_pixel_; }
    int y_upper_pixel() const { return y_upper_pixel_; }
    
    double scale_x()  const { return scale_x_; }
    double scale_y()  const { return scale_y_; }
    double step_val() const { return step_val_; }
    
    int CountPixelPosX(double x_ct) const;
    int CountPixelPosY(double y_ct) const;

    double CountAxisPosX(int x_pixel) const;
    double CountAxisPosY(int y_pixel) const;

    void Draw(GraphicSpace* editor, Color col = Color(255, 255, 255, 255), Color axis_col = Color(0, 0, 255, 255)) const;
    ~CoordinateSus(){}
};
//----------------------------------------------------------------------------------------//

class Vector{

private:
    geom::Vector vtor;
    Color col;

    int CheckCoordInCTS(const CoordinateSus& cts, uint x, uint y);

    void DrawVtor(GraphicSpace* editor, const Vector& vt_to_draw, const CoordinateSus& ct_sus, Color col = Color(255, 0, 0));
    void DrawVtor(GraphicSpace* editor, const Vector& vt_to_draw, const CoordinateSus& ct_sus, double x_init, double y_init, Color col = Color(255, 0, 0));
    void DrawVtor(GraphicSpace* editor, const Vector& vt_to_draw, const CoordinateSus& ct_sus, const Vector& vt_init, Color col = Color(255, 0, 0));

};

} // namespace prim

#endif // DRAWER_H
