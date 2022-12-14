#include "logger.h"
#include "EventWrapper.h"
#include "Widget.h"
//? convertFromStandardEvent()?

// TODO: other stuff
booba::Event* convertToStandartEvent(stImage* space, const Event* event){

    booba::Event* stEvent = new booba::Event();

    if(event->type() == T_EVENT::unknown){
        stEvent->type = booba::EventType::NoEvent;
    }

    if(event->type() == T_EVENT::mouseClick || event->type() == T_EVENT::mouseReleased){
        booba::MouseButtonEventData data;

        data.x = ManipulatorsContext::activeContext.mousePos().x - space->pos().x;
        data.y = ManipulatorsContext::activeContext.mousePos().y - space->pos().y;

        const MouseButtonPressedEvent* castedEvent = reinterpret_cast<const MouseButtonPressedEvent*>(event);

        if(castedEvent->tButton() == T_MOUSE_BUTTON::L)
            data.button = booba::MouseButton::Left;
        else
            data.button = booba::MouseButton::Right;

        data.shift = ManipulatorsContext::activeContext.isKeyPressed(T_KEY::LShift)     || ManipulatorsContext::activeContext.isKeyPressed(T_KEY::RShift);
        data.alt   = ManipulatorsContext::activeContext.isKeyPressed(T_KEY::LAlt)       || ManipulatorsContext::activeContext.isKeyPressed(T_KEY::RAlt);
        data.ctrl  = ManipulatorsContext::activeContext.isKeyPressed(T_KEY::LControl)   || ManipulatorsContext::activeContext.isKeyPressed(T_KEY::RControl);

        stEvent->Oleg.mbedata = data;

        if(event->type() == T_EVENT::mouseClick){
            stEvent->type = booba::EventType::MousePressed;
        }
        else if(event->type() == T_EVENT::mouseReleased){
            stEvent->type = booba::EventType::MouseReleased;
        }
    }
    else if(event->type() == T_EVENT::mouseMoved){
        booba::MotionEventData data;

        const MouseMovedEvent* casted_event = (const MouseMovedEvent*)(event);

        data.rel_x = casted_event->oldPos().x - space->pos().x;
        data.rel_y = casted_event->oldPos().y - space->pos().y;
        data.x     = casted_event->newPos().x - space->pos().x;
        data.y     = casted_event->newPos().y - space->pos().y;

        stEvent->Oleg.motion = data;
        stEvent->type = booba::EventType::MouseMoved;
    }
    else if(event->type() == T_EVENT::keyPressed){
        stEvent->type = booba::EventType::ButtonClicked;

        booba::ButtonClickedEventData data;

        KeyPressedEvent* casted_event = (KeyPressedEvent*)(event);
        
        //? meaning
        data.id = static_cast<int>(casted_event->key());

        stEvent->Oleg.bcedata = data;
    }
    /*
    else if(event->type() == T_EVENT::sliderMoved){
        stEvent->type = booba::EventType::SliderMoved;

        booba::ScrollMovedEventData data;

        SliderMovedEvent* casted_event = (SliderMovedEvent*)(event);
        
        data.id = (uint64_t)casted_event->p_slider();
        data.value = casted_event->ratio() * casted_event->p_slider()->width();

        stEvent->Oleg.smedata = data;
    } 
    */
    else{
        // TODO: other events
        EDLOG("unrecognized type from event %p", event);
    }

    return stEvent;
}

stImage::stImage(CanvasWidget* canvas):
    pArea_(canvas->drawableLayer()),
    pos_(canvas->realPos())
{}

stImage::stImage(DrawableArea* area):
    pArea_(area),
    pos_()
{}

size_t stImage::getH(){
    return pArea_->size().y;
}

size_t stImage::getW(){
    return pArea_->size().x;
}

uint32_t stImage::getPixel(size_t x, size_t y){
    return convertTosColor(pArea_->getPixel({x, y}));
}

void stImage::setPixel(size_t x, size_t y, uint32_t color){
    pArea_->setPixel({x, y}, convertFromsColor(color));
    return;
}
