#include "stImage.h"

booba::Image::~Image() {}

stImage::stImage(PixelBuffer* storage, uint x, uint y, uint width, uint height, uint globX, uint globY):
    storage_(storage), x_(x), y_(y), width_(width), height_(height), glob_x_(globX), glob_y_(globY){}

uint32_t stImage::getH(){
    return height_;
}

uint32_t stImage::getX(){
    return width_;
}

uint32_t stImage::getPixel(int32_t x, int32_t y){

    return static_cast<uint32_t>(storage_->getPixel(x + x_, y + y_));
}

void stImage::putPixel(uint32_t x, uint32_t y, uint32_t color){
    
    // TODO: if static cast is impossible make methods

    storage_->drawPixel(x + x_, y + y_, Color(0, 0, 0));
    return;
}

// TODO:
uint32_t& stImage::operator()(uint32_t x, uint32_t y){

    return tmp;
}

// TODO:
const uint32_t& stImage::operator()(uint32_t x, uint32_t y) const{

    return tmp;
}

uint stImage::globX() const{
    return glob_x_;
}

uint stImage::globY() const{
    return glob_y_;
}
