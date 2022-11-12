#include "Slider.h"

HSlider::HSlider(uint x, uint y, uint width, uint height, double visible_area_ratio):
    ContainerWidget(x, y, width, height),
    butt_(0, 0, (uint)((double)width * visible_area_ratio), height)
{
    // TODO: changable color for elements
    connect(&butt_);

    // TODO:
    if(visible_area_ratio >= 1){
        is_visible_ = false;
    }

    butt_.setTexture(Color(50, 50, 50));

    return;
}

void HSlider::onMouseLClick(const MouseLClickEvent* event){
    double ratio = ((double)(event->x() - rx())) / (double)width();

    int new_butt_x_pos = (int)(event->x() - rx()) - (int)(butt_.width() / 2);

    if(new_butt_x_pos < 0) new_butt_x_pos = 0;
    else if(new_butt_x_pos + butt_.width() > width()) new_butt_x_pos = width() - butt_.width();

    butt_.x(new_butt_x_pos);

    butt_.RequireRender();

    SliderMovedEvent slider_event(ratio);
    throwEvent(&slider_event);

    return;
}

hSlider_.update_limit(ext_width_);
vSlider_.update_limit(ext_height_);
 