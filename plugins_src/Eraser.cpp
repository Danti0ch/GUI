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

static void draw_dot(booba::Image* image, int x, int y, int size){
    for (int32_t curX = std::max(0, x - size); curX < std::min(int32_t(image->getX()), x + size); curX++) {
        for (int32_t curY = std::max(0, y - size); curY < std::min(int32_t(image->getH()), y + size); curY++) {
            image->putPixel(curX, curY, 0/*booba::APPCONTEXT->fgColor*/);
        }
    }

    return;
}

static void draw_vert_line(booba::Image* image, uint x, uint yF, uint yS, uint pen_size){

    uint y_init = std::min(yF, yS);
    uint y_end  = std::max(yF, yS);

    for(uint cur_y = y_init; cur_y <= y_end; cur_y++){
        draw_dot(image, x, cur_y, pen_size);
    }
    return;
}

// TODO: optimize by making visited array
static void draw_line(booba::Image* image, uint xF, uint xS, LagrangePolynom& polynom_, uint pen_size){

    assert(xF != xS);

    double x_init = std::min(xF, xS);
    double x_end  = std::max(xF, xS);
    
    double dx = (x_end - x_init) / 100;
    for(double cur_x = x_init; cur_x <= x_end; cur_x += dx){

        double cur_y = polynom_.interpolate(cur_x);

        if((uint)cur_y >= image->getH() || (uint)cur_x >= image->getX()) continue;
        draw_dot(image, (int)cur_x, (int)cur_y, pen_size);
    }
    return;
}

PenTool::PenTool():
    AbstractTool(),
    isLButtonPressed(false),
    polynom_(),
    pen_size_(4)
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
            polynom_.add(event->Oleg.motion.rel_x, event->Oleg.motion.rel_y);        
        }
        polynom_.add(event->Oleg.motion.x, event->Oleg.motion.y);        

        if(event->Oleg.motion.rel_x == event->Oleg.motion.x){
            draw_vert_line(image, event->Oleg.motion.x, event->Oleg.motion.rel_y, event->Oleg.motion.y, pen_size_);
        }
        else{
            draw_line(image, event->Oleg.motion.rel_x, event->Oleg.motion.x, polynom_, pen_size_);
        }
    }
    else if(event->type == booba::EventType::ScrollbarMoved){
        
    }
    return;
}

void PenTool::buildSetupWidget(){

    sizeControllerScrollBar_ = booba::createScrollbar(5, 5, 40, 3);
    booba::createLabel(5, 8, 20, 15, "Pen Size");

    return;
}
