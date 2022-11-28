#include "Window.h"
#include <iostream>

Window::Window(uint width, uint height):
    ContainerWidget(width, height),
    space_(width, height),
    manager_()
{   
    //! ok?
    p_manager_ = &manager_;
}

void Window::exec(){
    Event* event = NULL;
    bool was_event = false;

    coreDraw();

    // TODO: fix
    space_.drawPixelBuffer(0, 0, buff_);
    space_.show();

    while(space_.isOpen()){
        while(space_.extractEvent(&event)){
            was_event = true;
            manager_.ProcessHandlers(event);
            delete event;
        }
        if(was_event){
            coreDraw();
            space_.drawPixelBuffer(0, 0, buff_);
            space_.show();
            was_event = false;
        }
    }

    return;
}

void Window::add(Widget* widget, uint x, uint y){
    ContainerWidget::connect(widget, x, y);
    return;
}

void Window::add(Widget* widget, Widget* from_widget, LINKAGE_MODE mode, uint indent_val, uint offset){
    ContainerWidget::connect(widget, from_widget, mode, indent_val, offset);
    return;
}

void Window::remove(Widget* widget){
    ContainerWidget::remove(widget);
    return;
}
