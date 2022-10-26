#include "Widget.h"
#include "Window.h"

// space_ and event manager to global

Widget::Widget(uint x, uint y, uint width, uint height):
    x_(x), y_(y), gx_(x), gy_(y), width_(width), height_(height), texture_(), space_(NULL), manager_(NULL), focused_(false){}

Widget::Widget(ContainerWidget* parent_widget, uint x, uint y, uint width, uint height):
    x_(x), y_(y), gx_(parent_widget->x() + x), gy_(parent_widget->y() + y), width_(width), height_(height), texture_(), space_(parent_widget->space_), manager_(parent_widget->manager_), focused_(false)
{
    parent_widget->connect(*this);
}

Widget::~Widget(){}
//----------------------------------------------------------------------------------------//

void Widget::fullDraw() /* TODO: final??? */{
    if(space_ == NULL) return;

    texture_.draw(space_, x_, y_, x_ + width_ - 1, y_ + height_ - 1, TEXTURE_INSERT_MODE::SCRETCHING);
    draw();
    return;
}
//----------------------------------------------------------------------------------------//

bool Widget::addEventHandler(T_EVENT event_id, T_HANDLER_FUNC p_handler){
    if(p_core_window_ == NULL) return false;

    // TODO: refactor
    p_core_window_->event_manager.addHandler(event_id, this, p_handler, NULL);
    return true;  
}
//----------------------------------------------------------------------------------------//

bool Widget::RemoveEventHandler(T_EVENT event_id, T_HANDLER_FUNC p_handler){
    if(p_core_window_ == NULL) return false;

    p_core_window_->event_manager.removeHandler(event_id, this, p_handler);
    return true;
}
//----------------------------------------------------------------------------------------//

void Widget::resize(uint x, uint y, uint width, uint height){
    x_      = x;
    y_      = y;
    width_  = width;
    height_ = height;
}
//----------------------------------------------------------------------------------------//
