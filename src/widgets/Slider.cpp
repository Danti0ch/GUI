#include "Slider.h"

// TODO: real_x(), real_y()

//? button variable pos in constructor
HSlider::HSlider(uint x, uint y, uint width, uint height, uint butt_width):
    Widget(x, y, width, height),
    ratio_(0),
    butt_(0, 0, butt_width, height)
{
    // TODO: remove
    butt_.setTexture(Color(50, 50, 50));
}

HSlider::~HSlider(){}

void HSlider::onMouseLClick(const MouseLClickEvent* event){
    NASSERT(event);

    int new_butt_x_pos = (int)(event->x() - real_x()) - (int)(butt_.width() / 2);

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

void HSlider::draw(){
    butt_.coreDraw();

    PixelBuffer* p_buf = GetPointerOnPixBuff();
    p_buf->drawPixelBuffer(butt_.x(), butt_.y(), butt_.pixBuff());
    return;
}

VSlider::VSlider(uint x, uint y, uint width, uint height, uint butt_height):
    Widget(x, y, width, height),
    ratio_(0),
    butt_(0, 0, width, butt_height)
{
    // TODO: remove
    butt_.setTexture(Color(50, 50, 50));
}

VSlider::~VSlider(){}

void VSlider::onMouseLClick(const MouseLClickEvent* event){
    NASSERT(event);

    int new_butt_y_pos = (int)(event->y() - real_y()) - (int)(butt_.height() / 2);

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

//? ok
void VSlider::draw(){
    butt_.coreDraw();

    PixelBuffer* p_buf = GetPointerOnPixBuff();
    p_buf->drawPixelBuffer(butt_.x(), butt_.y(), butt_.pixBuff());
    return;
}
