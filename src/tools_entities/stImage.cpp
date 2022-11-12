#include "stImage.h"

stImage::stImage(uint width, uint height):
    storage_(width, height){}

uint32_t stImage::getH(){
    return storage_.height();
}

uint32_t stImage::getX(){
    return storage_.width();
}

uint32_t stImage::getPixel(int32_t x, int32_t y){

    return static_cast<uint32_t>(storage_.getPixel(x, y));
}

void stImage::putPixel(uint32_t x, uint32_t y, uint32_t color){
    
    // TODO: if static cast is impossible make methods
    storage_.drawPixel(x, y, static_cast<Color>(color));

    return;
}

uint32_t& stImage::operator()(uint32_t x, uint32_t y){

    return const_cast<uint32_t&>(stImage::operator()(x, y));
}

const uint32_t& stImage::operator()(uint32_t x, uint32_t y) const{

    return static_cast<const uint32_t&>(storage_.getPixel(x, y));
}

stImage::~stImage(){}
