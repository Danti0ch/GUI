#include "Window.h"
#include <iostream>

Window::Window(uint width, uint height):
    ContainerWidget(0, 0, width, height),
    space_(width, height),
    pix_buf_(width, height),
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
    space_.drawPixelBuffer(0, 0, pix_buf_);
    space_.show();

    while(true){}
    while(space_.isOpen()){
        while(space_.extractEvent(&event)){
            was_event = true;
            manager_.ProcessHandlers(event);
            delete event;
        }
        if(was_event){
            coreDraw();
            space_.drawPixelBuffer(0, 0, pix_buf_);
            space_.show();
            was_event = false;
        }
    }

    return;
}
