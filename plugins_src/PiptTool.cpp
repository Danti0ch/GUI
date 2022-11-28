#include "StandartTools.h"
#include <iostream>
#include <assert.h>
#include "logger.h"

TOOL_INIT(PiptTool)

extern booba::ApplicationContext* APPCONTEXT;

PiptTool::PiptTool():
    AbstractTool()
{}

void PiptTool::apply(booba::Image* image, const booba::Event* event) {

    if(event->type == booba::EventType::MousePressed){
        if(event->Oleg.mbedata.button == booba::MouseButton::Left){
            
            APPCONTEXT->fgColor = image->getPixel(event->Oleg.mbedata.x, event->Oleg.mbedata.y);
        }
        else if(event->Oleg.mbedata.button == booba::MouseButton::Right){
            
            APPCONTEXT->bgColor = image->getPixel(event->Oleg.mbedata.x, event->Oleg.mbedata.y);
        }
    }
    return;
}
