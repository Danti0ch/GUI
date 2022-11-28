#include "logger.h"
#include "EventWrapper.h"

// TODO: rename
booba::Event* convertToStandartEvent(const stImage* space, const Event* event){

    booba::Event* stEvent = new booba::Event();

    if(event->type() == T_EVENT::unknown){
        stEvent->type = booba::EventType::NoEvent;
    }

    if(event->type() == T_EVENT::mouseLClick || event->type() == T_EVENT::mouseReleased || event->type() == T_EVENT::mouseMoved){
        booba::MouseButtonEventData data;

        MouseEvent* casted_event = (MouseEvent*)(event);
        data.x = casted_event->state()->x() - space->globX();
        data.y = casted_event->state()->y() - space->globY();

        data.button = booba::MouseButton::Left;
        data.shift = casted_event->special_keys()->lShift();
        data.alt   = casted_event->special_keys()->alt();
        data.ctrl  = casted_event->special_keys()->ctrl();

        stEvent->Oleg.mbedata = data;

        if(event->type() == T_EVENT::mouseLClick){
            stEvent->type = booba::EventType::MousePressed;
        }
        else if(event->type() == T_EVENT::mouseReleased){
            stEvent->type = booba::EventType::MouseReleased;
        }
        else if(event->type() == T_EVENT::mouseMoved){
            stEvent->type = booba::EventType::MouseMoved;
        }
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
