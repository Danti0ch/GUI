/*#include "tools.hpp"
#include "Event.h"
#include "logger.h"

/*
class Event
    {
    public:
        EventType type;
        union 
        {
            MotionEventData motion;
            MouseButtonEventData mbedata;
            ButtonClickedEventData bcedata;
            ScrollMovedEventData smedata;
            CanvasEventData cedata;
        } Oleg; //Object loading event group.
    };



// TODO: rename
booba::Event* convertToStandartEvent(const Event* event){

    booba::Event* stEvent = new booba::Event();

    if(event->type() == T_EVENT::unknown){
        stEvent->type = booba::EventType::NoEvent;
    }
    else if(event->type() == T_EVENT::mouseLClick){
        stEvent->type = booba::EventType::MousePressed;

        booba::MouseButtonEventData data;

        MouseLClickEvent* casted_event = (MouseLClickEvent*)(event);
        data.x = casted_event->x();
        data.y = casted_event->y();

        data.button = booba::MouseButton::Left;
        data.shift = data.alt = data.ctrl = false;
        stEvent->Oleg.mbedata = data;
    }
    else if(event->type() == T_EVENT::keyPressed){
        stEvent->type = booba::EventType::ButtonClicked;

        booba::ButtonClickedEventData data;

        KeyPressedEvent* casted_event = (KeyPressedEvent*)(event);
        
        //? meaning
        data.id = casted_event->key();

        stEvent->Oleg.bcedata = data;
    }
    else{
        // TODO: other events
        EDLOG("unrecognized type from event %p", event);
    }

    return stEvent;
}
*/
//? convertFromStandardEvent()?
