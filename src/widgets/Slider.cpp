#include "Slider.h"

// TODO: remove copypast
//? button variable pos in constructor
HSlider::HSlider(uint width, uint height, uint butt_width):
    ContainerWidget(width, height),
    ratio_(0),
    butt_(butt_width, height)
{
    // TODO: remove
    butt_.setTexture(Color(50, 50, 50));
    ContainerWidget::connect(&butt_, 0, 0);
}

HSlider::~HSlider(){}

void HSlider::onMouseLClick(const MouseLClickEvent* event){
    NASSERT(event);

    if(!isPointInside(this, event->state()->x(), event->state()->y())){
        return;
    }

    if(isVisible() == false) return;
    int new_butt_x_pos = (int)(event->state()->x() - real_x()) - (int)(butt_.width() / 2);

    if(new_butt_x_pos < 0) new_butt_x_pos = 0;
    else if(new_butt_x_pos + butt_.width() > width()) new_butt_x_pos = width() - butt_.width();

    butt_.x(new_butt_x_pos);

    // TODO: fix
    butt_.RequireRender();
    RequireRender();

    double ratio = (double)new_butt_x_pos / (double)(width() - butt_.width());
    SliderMovedEvent slider_event(this, ratio);
    throwEvent(&slider_event);

    return;
}

void HSlider::ratio(double val){
    assert(val >= 0 && val <= 1);

    ratio_ = val;
    RequireRender();
}

VSlider::VSlider(uint width, uint height, uint butt_height):
    ContainerWidget(width, height),
    ratio_(0),
    butt_(width, butt_height)
{
    // TODO: remove
    butt_.setTexture(Color(50, 50, 50));
    ContainerWidget::connect(&butt_, 0, 0);
}

VSlider::~VSlider(){}

void VSlider::onMouseLClick(const MouseLClickEvent* event){
    NASSERT(event);

    if(!isPointInside(this, event->state()->x(), event->state()->y())){
        return;
    }

    if(isVisible() == false) return;
    int new_butt_y_pos = (int)(event->state()->y() - real_y()) - (int)(butt_.height() / 2);

    if(new_butt_y_pos < 0) new_butt_y_pos = 0;
    else if(new_butt_y_pos + butt_.height() > height()) new_butt_y_pos = height() - butt_.height();

    butt_.y(new_butt_y_pos);
    butt_.RequireRender();
    RequireRender();

    double ratio = (double)new_butt_y_pos / (double)(height() - butt_.height());
    SliderMovedEvent slider_event(this, ratio);

    throwEvent(&slider_event);

    return;
}

void VSlider::ratio(double val){
    assert(val >= 0 && val <= 1);

    ratio_ = val;
    RequireRender();
}
