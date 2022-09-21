#ifndef TESTS_H
#define TESTS_H

#include "graphic_lib_wrapper.h"
#include "geometry_objects.h"

class ActionVectorsRender : public gglib::GraphicSpace{

private:
    gglib::CoordinateSus time_cts_group_[3];
    gglib::CoordinateSus cts1_;

    gglib::Button butt_reset_, butt_speed_, butt_exit_;

    double  cts1_ct_x_, cts1_ct_y_;
    uint    time_arrow_speed_ratio_;
    uint    cur_sec_val_;
    clock_t init_time_;

    void MouseButtonPressHandler(uint x_pos, uint y_pos);
    void Update();
public:
    ActionVectorsRender();
};
//----------------------------------------------------------------------------------------//

class SphereRender : public gglib::GraphicSpace{

private:
    gglib::CoordinateSus image_cts_, manip_cts_;

    double x_manip_, y_manip_;

    gglib::Color get_sphere_pixel_color(uint x_pix, uint y_pix);
    void  draw_sphere();
    void  MouseButtonPressHandler(uint x_pos, uint y_pos);
public:
    SphereRender();
};
//----------------------------------------------------------------------------------------//

#endif // TESTS_H
