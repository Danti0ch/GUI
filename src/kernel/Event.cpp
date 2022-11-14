#include "Event.h"
#include "Widget.h"

bool MouseEvent::check(const Widget* widget) const{

    if(widget->real_x() <= x_ && widget->width()  + widget->real_x() >= x_ && 
        widget->real_y() <= y_ && widget->height() + widget->real_y() >= y_) return true;
    return false;
}

bool KeyPressedEvent::check(const Widget* widget) const{
    if(widget->isFocused()) return true;
    return false;
}

bool SliderMovedEvent::check(const Widget* widget) const{
    return true;    
}
