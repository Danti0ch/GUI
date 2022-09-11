#include "drawer.h"
#include <math.h>

const double EPS = 1e-8;
/*
double Function(double x){

    if(fabs(x) < EPS) return 0;
    return x / sin(x);
}

void DrawGraphic(sf::RenderWindow* window, CoordinateSus* ct_sus){

    Point x_ax_start_point(ct_sus->x_lower_lim(), 0);
    Point y_ax_start_point(0, ct_sus->y_lower_lim());
    
    Vector x_ax_vtor(ct_sus->x_upper_lim() - ct_sus->x_lower_lim(), 0, x_ax_start_point);
    Vector y_ax_vtor(0, ct_sus->y_upper_lim() - ct_sus->y_lower_lim(), y_ax_start_point);

    x_ax_vtor.Draw(window, ct_sus);
    y_ax_vtor.Draw(window, ct_sus);

    double step_val    = ct_sus->get_step_val();
    double x_lower_lim = ct_sus->x_lower_lim();
    double x_upper_lim = ct_sus->x_upper_lim();

    Point begin_point(x_lower_lim, Function(x_lower_lim));

    double y_last_val = Function(x_lower_lim + step_val);
    Vector last_vec(step_val, y_last_val - Function(x_lower_lim), begin_point);

    last_vec.Draw(window, ct_sus);

    for(double x_pos = x_lower_lim + step_val * 2; x_upper_lim - x_pos > -EPS; x_pos += step_val){
        
        double y_cur_val = Function(x_pos);
        Vector cur_vec(step_val, y_cur_val - y_last_val, &last_vec);

        cur_vec.Draw(window, ct_sus);
        last_vec   = cur_vec;
        y_last_val = y_cur_val;
    }
  
    return;
}
//----------------------------------------------------------------------------------------//
*/
