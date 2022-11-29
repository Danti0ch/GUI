#include "logger.h"
#include "EventWrapper.h"
#include "Widget.h"

// TODO: rename
booba::Event* convertToStandartEvent(const stImage* space, const Event* event){

    booba::Event* stEvent = new booba::Event();

    std::cout << (int)event->type() << "\n";

    if(event->type() == T_EVENT::unknown){
        stEvent->type = booba::EventType::NoEvent;
    }

    if(event->type() == T_EVENT::mouseLClick || event->type() == T_EVENT::mouseReleased){
        booba::MouseButtonEventData data;

        MouseEvent* casted_event = (MouseEvent*)(event);

        data.x = casted_event->state()->x() - space->x();
        data.y = casted_event->state()->y() - space->y();

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
    else if(event->type() == T_EVENT::mouseMoved){
        booba::MotionEventData data;

        MouseEvent* casted_event = (MouseEvent*)(event);

        data.rel_x = casted_event->state()->last_x() - space->x();
        data.rel_y = casted_event->state()->last_y() - space->y();
        data.x     = casted_event->state()->x() - space->x();
        data.y     = casted_event->state()->y() - space->y();

        stEvent->Oleg.motion = data;
        stEvent->type = booba::EventType::MouseMoved;
    }
    else if(event->type() == T_EVENT::keyPressed){
        stEvent->type = booba::EventType::ButtonClicked;

        booba::ButtonClickedEventData data;

        KeyPressedEvent* casted_event = (KeyPressedEvent*)(event);
        
        //? meaning
        data.id = casted_event->key();

        stEvent->Oleg.bcedata = data;
    }
    else if(event->type() == T_EVENT::sliderMoved){
        stEvent->type = booba::EventType::ScrollbarMoved;

        booba::ScrollMovedEventData data;

        SliderMovedEvent* casted_event = (SliderMovedEvent*)(event);
        
        data.id = (uint64_t)casted_event->p_slider();
        data.value = casted_event->ratio() * casted_event->p_slider()->width();

        stEvent->Oleg.smedata = data;
    }
    else{
        // TODO: other events
        EDLOG("unrecognized type from event %p", event);
    }

    return stEvent;
}

//? convertFromStandardEvent()?
