#ifndef WINDOW_H
#define WINDOW_H

#include "glib_wrapper.h"
#include "Texture.h"
#include "ContainerWidget.h"
#include <iostream>

/*
struct EventHandler{
    Widget* p_widget;
    Event*  p_event;
};
*/
class EventManager{
public:
    EventManager():
        handlers_(N_CORE_EVENTS){}
    
    void processEvents(const CoreEvent* core_event){
        std::list<EventHandler>::iterator iter = handlers_[core_event.id()].begin();

        // TODO: можно ли избавиться от id
        while(; iter != handlers_[core_event.id()].end(); iter++){
            if((*iter)->apply(core_event)){
                (*iter)->proccessHandlers();
            }
        }
        return;
    }

    void addEvent(const Event* event){
        for(uint n_core_event_id = 0; n_core_event_id < event->core_events.size(); n_core_event_id++){
            handlers[event->core_events[n_core_event_id]].push_back(event);
        }
        return;
    }

    void removeEvent(const Event* event){
        for(uint n_core_event_id = 0; n_core_event_id < event->core_events.size(); n_core_event_id++){
            handlers[event->core_events[n_core_event_id]].push_back(event);
        }
    }

    ~EventManager(){}
private:
    std::vector<std::list<const Event*>> handlers_;
};
class Window{
public:
    Window(uint width, uint height, const Texture& texture):
        space(width, height),
        storage_widget(0, 0, width, height, texture.)
    {}
    
    Window(uint width, uint height):
        space(width, height),
        storage_widget(0, 0, width, height)
    {}
    
    void exec(){
        CoreEvent* core_event = new CoreEvent(T_CORE_EVENT::UNDEFINED);
        
        while(space.isopen()){
            while(space.handleEvent(core_event)){
                e_manager.processEvents(core_event);
            }

            space.show();
        }
        delete core_event;
        return;
    }

// TODO: распространяется на потомки?
friend class Widget;
private:
    ContainerWidget storage_widget;
    GraphicSpace    space;
    EventManager    e_manager;
};

#endif // WINDOW_H
