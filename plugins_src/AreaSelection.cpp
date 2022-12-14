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
                if(x + x_i > img->getW() || y + y_i > img->getH()) continue;
                img->setPixel(x + x_i, y + y_i, storage_[y_i * width_ + x_i]);
            }
        }    
    }

private:
    uint32_t* storage_;
    uint width_, height_;
};

const int FrameWidth = 2;

void drawFrame(booba::Image* layer, RectangleArea area){

    for(uint x = area.pos.x; x < area.size.x; x++){
        for(int depth = 0; depth < FrameWidth; depth++){
            layer->setPixel(x, area.pos.y + depth, convertTosColor(Color::BLACK));
        }
    }

    for(uint x = area.pos.x; x < area.size.x; x++){
        for(int depth = 0; depth < FrameWidth; depth++){
            layer->setPixel(x, area.size.y - depth - 1, convertTosColor(Color::BLACK));
        }
    }

    for(uint y = area.pos.y; y < area.size.y; y++){
        for(int depth = 0; depth < FrameWidth; depth++){
            layer->setPixel(area.pos.x + depth, y, convertTosColor(Color::BLACK));
        }
    }


    for(uint y = area.pos.y; y < area.size.y; y++){
        for(int depth = 0; depth < FrameWidth; depth++){
            layer->setPixel(area.size.x - depth - 1, y, convertTosColor(Color::BLACK));
        }
    }

    return;
}

AreaSelectionTool::AreaSelectionTool():
    AbstractTool(),
    buff_(NULL),
    canvas_id_(0),
    area_width_(0), area_height_(0),
    x_(0), y_(0){}

void AreaSelectionTool::apply(booba::Image* image, const booba::Event* event) {

    if(event->type == booba::EventType::MousePressed){

        isMouseClicked_ = true;

        if(event->Oleg.mbedata.ctrl && buff_){
            buff_->draw(event->Oleg.mbedata.x, event->Oleg.mbedata.y, image);
        }

        x_ = event->Oleg.mbedata.x;
        y_ = event->Oleg.mbedata.y;
    }
    else if(event->type == booba::EventType::MouseReleased){

        isMouseClicked_ = false;

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
    else if(event->type == booba::EventType::MouseMoved && isMouseClicked_){

        uint newX = event->Oleg.motion.x;
        uint newY = event->Oleg.motion.y;

        drawFrame(booba::getHiddenLayerID(), RectangleArea({std::min(x_, newX), std::min(y_, newY)}, {std::max(x_, newX), std::max(y_, newY)}));
    }

    return;
}

const char* AreaSelectionTool::getTexture(){
    return "plugins/textures/AreaSelect.png";
}
