#include "Widget.h"

EventManager::EventManager():
    widgets_(){}

void EventManager::addWidget(Widget* widget){
    widgets_.push_back(widget);
    return;
}

void EventManager::removeWidget(Widget* widget){
    widgets_.remove(widget);
    return;
}

void EventManager::ProcessHandlers(const Event* event){

    std::list<Widget*>::iterator iter = widgets_.begin();
    
    // TODO: make queue for unhandled events
    for(; iter != widgets_.end(); iter++){
        //if(event->check(*iter)){
            (*iter)->triggerEvent(event);
        //}
    }
    return;
}
