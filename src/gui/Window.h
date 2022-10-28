#ifndef WINDOW_H
#define WINDOW_H

#include "glib_wrapper.h"
#include "Texture.h"
#include "Widget.h"

#include "logger.h"

class Window : public ContainerWidget{
public:

    Window(uint width, uint height):
        space(width, height),
        ContainerWidget(0, 0, width, height)
    {
        p_core_window_ = this;
    }
    
    void exec(){
        Event* event = NULL;
        bool was_event = false;

        fullDraw();
        space.show();

        while(space.isOpen()){
            while(space.extractEvent(&event)){
                was_event = true;
                event_manager.processHandlers(event);
                delete event;
            }
            if(was_event){
                fullDraw();
                space.show();
                was_event = false;
            }
        }

        return;
    }

    friend class Widget;
private:
    GraphicSpace    space;
    EventManager    event_manager;
};

#endif // WINDOW_H
