#include "StandartTools.h"
#include <iostream>

TOOL_INIT(AreaSelectionTool)

class PixBuff{
public:
    PixBuff(uint x, uint y, uint width, uint height, booba::Image* img):
        width_(width), height_(height)
    {
        assert(width != 0 && height != 0);

        storage_ = new uint32_t[width * height];

        for(uint y_i = 0; y_i < height; y_i++){
            for(uint x_i = 0; x_i < width; x_i++){
                storage_[y_i * width + x_i] = img->getPixel(x + x_i, y + y_i);
            }
        }
    }

    ~PixBuff(){ delete storage_; }

    void draw(uint x, uint y, booba::Image* img){
    
        for(uint y_i = 0; y_i < height_; y_i++){
            for(uint x_i = 0; x_i < width_; x_i++){
                if(x + x_i > img->getX() || y + y_i > img->getH()) continue;
                img->putPixel(x + x_i, y + y_i, storage_[y_i * width_ + x_i]);
            }
        }    
    }

private:
    uint32_t* storage_;
    uint width_, height_;
};

AreaSelectionTool::AreaSelectionTool():
    AbstractTool(),
    buff_(NULL),
    canvas_id_(0),
    area_width_(0), area_height_(0),
    x_(0), y_(0){}

void AreaSelectionTool::apply(booba::Image* image, const booba::Event* event) {

    if(event->type == booba::EventType::MousePressed){

        if(event->Oleg.mbedata.ctrl && buff_){
            buff_->draw(event->Oleg.mbedata.x, event->Oleg.mbedata.y, image);
        }

        x_ = event->Oleg.mbedata.x;
        y_ = event->Oleg.mbedata.y;
    }
    else if(event->type == booba::EventType::MouseReleased){

        if(event->Oleg.mbedata.x == x_ || event->Oleg.mbedata.y == y_) return;
        if(event->Oleg.mbedata.x > x_){
            area_width_ = event->Oleg.mbedata.x - x_;
        }
        else{
            area_width_ = x_ - event->Oleg.mbedata.x;
            x_ = event->Oleg.mbedata.x;
        }

        if(event->Oleg.mbedata.y > y_){
            area_height_ = event->Oleg.mbedata.y - y_;
        }
        else{
            area_height_ = y_ - event->Oleg.mbedata.y;
            y_ = event->Oleg.mbedata.y;
        }

        if(buff_){
            delete buff_;
            buff_ = NULL;
        }

        buff_ = new PixBuff(x_, y_, area_width_, area_height_, image);
    }

    return;
}
