#include "Event.h"
#include "Widget.h"

bool MouseLClickEvent::check(const Widget* widget) const{

    if(widget->x() <= x_ && widget->width()  + widget->x() >= x_ && 
        widget->y() <= y_ && widget->height() + widget->y() >= y_) return true;
    return false;
}

bool KeyPressedEvent::check(const Widget* widget) const{
    if(widget->isFocused()) return true;
    return false;
}

bool SliderMovedEvent::check(const Widget* widget) const{
    return true;    
}
