#include "StandartTools.h"
#include <iostream>
#include <assert.h>
#include "logger.h"

static const uint POS_POISON = -1;
const uint SCROLL_BAR_WIDTH = 20;

const uint LINE_SIZE_ACTION = 4;

TOOL_INIT(PenTool) 
/*
    синопсис
    требуется быстрая кисточка со следующими фичами
    1. вариативный размер кисти
    2. интерполяция
        - вычисление промежуточных точек через полином лагранжa
    3. гладкое изображение линии
*/

void PenTool::draw_dot(booba::Image* image, int x, int y){

    for (int32_t curX = std::max(0, x - pen_size_); curX < std::min(int32_t(image->getW()), x + pen_size_); curX++) {
        for (int32_t curY = std::max(0, y - pen_size_); curY < std::min(int32_t(image->getH()), y + pen_size_); curY++) {
            
            if(isLButtonPressed)
                image->setPixel(curX, curY, booba::APPCONTEXT->fgColor);
            else
                image->setPixel(curX, curY, booba::APPCONTEXT->bgColor);            
        }
    }

    return;
}

void PenTool::draw_vert_line(booba::Image* image, uint x, uint yF, uint yS){

    uint y_init = std::min(yF, yS);
    uint y_end  = std::max(yF, yS);

    for(uint cur_y = y_init; cur_y <= y_end; cur_y++){
        draw_dot(image, x, cur_y);
    }
    return;
}

// TODO: optimize by making visited array
void PenTool::draw_line(booba::Image* image, uint xF, uint xS){

    assert(xF != xS);

    double x_init = std::min(xF, xS);
    double x_end  = std::max(xF, xS);
    
    double dx = (x_end - x_init) / 100;
    for(double cur_x = x_init; cur_x <= x_end; cur_x += dx){

        double cur_y = polynom_.interpolate(cur_x);

        if((uint)cur_y >= image->getH() || (uint)cur_x >= image->getW()) continue;
        draw_dot(image, (int)cur_x, (int)cur_y);
    }
    return;
}

PenTool::PenTool():
    AbstractTool(),
    isLButtonPressed(false),
    polynom_(),
    pen_size_(1)
{}

void PenTool::apply(booba::Image* image, const booba::Event* event) {

    const int32_t sqSize = 4;

    if(event->type == booba::EventType::MousePressed){
        lastPos_.x = event->Oleg.mbedata.x;
        lastPos_.y = event->Oleg.mbedata.y;

        if(event->Oleg.mbedata.button == booba::MouseButton::Left)
            isLButtonPressed = true;
        else
            isRButtonPressed = true;
    } 
    else if(event->type == booba::EventType::MouseReleased){
        if(event->Oleg.mbedata.button == booba::MouseButton::Left)
            isLButtonPressed = false;
        else
            isRButtonPressed = false;
        polynom_.reset();
    }
    else if(event->type == booba::EventType::MouseMoved && (isLButtonPressed || isRButtonPressed)){

        if(abs(lastPos_.x - event->Oleg.motion.x) < LINE_SIZE_ACTION && abs(lastPos_.y - event->Oleg.motion.y) < LINE_SIZE_ACTION) return;
        
        if(polynom_.is_empty()){
            polynom_.add(lastPos_.x, lastPos_.y);        
        }
        polynom_.add(event->Oleg.motion.x, event->Oleg.motion.y);        

        if(lastPos_.x == event->Oleg.motion.x){
            draw_vert_line(image, event->Oleg.motion.x, lastPos_.y, event->Oleg.motion.y);
        }
        else{
            draw_line(image, lastPos_.x, event->Oleg.motion.x);
        }

        lastPos_.x = event->Oleg.motion.x;
        lastPos_.y = event->Oleg.motion.y;
    }
    else if(event->type == booba::EventType::SliderMoved){
        pen_size_ = event->Oleg.smedata.value / 8;
    }

    return;
}

void PenTool::buildSetupWidget(){

    sizeControllerScrollBar_ = booba::createSlider(5, 5, 100, 12, 0, 0, 0);
    booba::createLabel(5, 17, 70, 20, "Pen Size");

    return;
}

const char* PenTool::getTexture(){
    return "plugins/textures/Pen.png";
}
