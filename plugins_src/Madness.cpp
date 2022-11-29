#include "StandartTools.h"
#include <iostream>
#include <assert.h>
#include "logger.h"

static const uint POS_POISON = -1;
static const uint DEFAULT_PEN_SIZE = 5;

TOOL_INIT(PenTool)
/*
    синопсис
    требуется быстрая кисточка со следующими фичами
    1. вариативный размер кисти
    2. интерполяция
        - вычисление промежуточных точек через полином лагранжa
    3. гладкое изображение линии
*/

static void draw_vert_line(booba::Image* image, uint x, uint yF, uint yS){

    uint y_init = std::min(yF, yS);
    uint y_end  = std::max(yF, yS);

    for(uint cur_y = y_init; cur_y <= y_end; cur_y++){
        image->putPixel(x, cur_y, 0);
    }
    return;
}

// TODO: optimize by making visited array
static void draw_line(booba::Image* image, uint xF, uint xS, LagrangePolynom& polynom_){

    assert(xF != xS);

    double x_init = std::min(xF, xS);
    double x_end  = std::max(xF, xS);
    
    double dx = (x_end - x_init) / 100;
    for(double cur_x = x_init; cur_x <= x_end; cur_x += dx){

        double cur_y = polynom_.interpolate(cur_x);

        if((uint)cur_y >= image->getH() || (uint)cur_x >= image->getX()) continue;
        
        image->putPixel((uint)cur_x, (uint)cur_y, 111);
    }

    return;
}

PenTool::PenTool():
    AbstractTool(),
    isLButtonPressed(false),
    polynom_()
{}

void PenTool::apply(booba::Image* image, const booba::Event* event) {

    const int32_t sqSize = 4;

    if(event->type == booba::EventType::MousePressed){
        isLButtonPressed = true;
    }   
    else if(event->type == booba::EventType::MouseReleased){
        isLButtonPressed = false;
        polynom_.reset();
    }
    else if(event->type == booba::EventType::MouseMoved && isLButtonPressed){
        if(polynom_.is_empty()){
            polynom_.add(0, 0);        
        }
        polynom_.add(event->Oleg.motion.x, event->Oleg.motion.y);        

        if(event->Oleg.motion.rel_x == event->Oleg.motion.x){
            draw_vert_line(image, event->Oleg.motion.x, 0, event->Oleg.motion.y);
        }
        else{
            draw_line(image, 0, event->Oleg.motion.x, polynom_);
        }
    }

    return;
}

void PenTool::buildSetupWidget(){

    sizeControllerScrollBar_ = booba::createScrollbar(5, 5, 40, 3);
    booba::createLabel(5, 8, 20, 15, "Pen Size");

    return;
}
