#include "Widget.h"

EventManager::EventManager():
    widgets_()
{}

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
    
    for(; iter != widgets_.end(); iter++){

        //?
        if((*iter)->isVisible())
            (*iter)->triggerEvent(event);
    }
    return;
}
