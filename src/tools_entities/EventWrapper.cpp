#include "logger.h"
#include "EventWrapper.h"

// TODO: rename
booba::Event* convertToStandartEvent(const stImage* space, const Event* event){

    booba::Event* stEvent = new booba::Event();

    if(event->type() == T_EVENT::unknown){
        stEvent->type = booba::EventType::NoEvent;
    }
    else if(event->type() == T_EVENT::mouseLClick){
        stEvent->type = booba::EventType::MousePressed;

        booba::MouseButtonEventData data;

        MouseLClickEvent* casted_event = (MouseLClickEvent*)(event);
        data.x = casted_event->state()->x() - space->globX();
        data.y = casted_event->state()->y() - space->globY();

        data.button = booba::MouseButton::Left;
        data.shift = data.alt = data.ctrl = false;
        stEvent->Oleg.mbedata = data;
    }
    else if(event->type() == T_EVENT::mouseReleased){
        stEvent->type = booba::EventType::MouseReleased;

        booba::MouseButtonEventData data;

        MouseReleasedEvent* casted_event = (MouseReleasedEvent*)(event);
        data.x = casted_event->state()->x() - space->globX();
        data.y = casted_event->state()->y() - space->globY();

        data.button = booba::MouseButton::Left;
        data.shift = data.alt = data.ctrl = false;
        stEvent->Oleg.mbedata = data;
    }
    else if(event->type() == T_EVENT::mouseMoved){
        stEvent->type = booba::EventType::MouseMoved;

        booba::MouseButtonEventData data;

        MouseMovedEvent* casted_event = (MouseMovedEvent*)(event);
        data.x = casted_event->state()->x() - space->globX();
        data.y = casted_event->state()->y() - space->globY();

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

//? convertFromStandardEvent()?
