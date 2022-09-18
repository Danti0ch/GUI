#ifndef TESTS_H
#define TESTS_H

#include "graphic_lib_wrapper.h"
#include "drawable_objects.h"

// TODO: параметр необходимости перерисовки
// TODO: наследование + виртуальные функции для евентов
class ActionVectorsRender{

private:
    GraphicSpace space_;
    CoordinateSus time_cts_group_[3];
    CoordinateSus cts1_;

    myButton butt_reset_, butt_speed_, butt_exit_;

    double  cts1_ct_x_, cts1_ct_y_;
    uint    time_arrow_speed_ratio_;
    uint    cur_sec_val_;
    clock_t init_time_;

    // TODO: чекнуть что значит
    static void mouse_press_event(GraphicSpace* space, int x_pos, int y_pos);
    static void update_handler(GraphicSpace* space);
public:
    ActionVectorsRender();

    void Init();
};

class SphereRender{

private:
    GraphicSpace space_;

    CoordinateSus image_cts_, manip_cts_;

    double x_manip_, y_manip_;

    void  draw_sphere();
    Color get_sphere_pixel_color(uint x_pix, uint y_pix);
    
    void  mouse_press_event(GraphicSpace* space, int x_pos, int y_pos);
    void  update_handler(GraphicSpace* space);
public:
    SphereRender();

    void Init();
};

#endif // TESTS_H
