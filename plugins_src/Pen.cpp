#include "StandartTools.h"
#include <iostream>
#include <assert.h>
#include "logger.h"

static const uint POS_POISON = -1;
static const uint DEFAULT_PEN_SIZE = 5;

TOOL_INIT(PenTool)

PenTool::PenTool():
    AbstractTool(),
    isLButtonPressed(false),
    prevX(POS_POISON), prevY(POS_POISON)
{}

void PenTool::apply(booba::Image* image, const booba::Event* event) {

    const int32_t sqSize = 4;

    if(event->type == booba::EventType::MousePressed){
        prevX = event->Oleg.mbedata.x;
        prevY = event->Oleg.mbedata.y;

        isLButtonPressed = true;
    }   
    else if(event->type == booba::EventType::MouseReleased){
        prevX = POS_POISON;
        prevY = POS_POISON;

        isLButtonPressed = false;
    }
    else if(event->type == booba::EventType::MouseMoved && isLButtonPressed){
        assert(prevX != POS_POISON && prevY != POS_POISON);
        MDLOG("Line (%u, %u)->(%u, %u) drawed", prevX, prevY, event->Oleg.mbedata.x, event->Oleg.mbedata.y);

        prevX = event->Oleg.mbedata.x;
        prevY = event->Oleg.mbedata.y;
    }

    return;
}
