#ifndef ST_IMAGE_H
#define ST_IMAGE_H

// TODO:

#include "tools.hpp"
#include "glib_wrapper.h"
//? maybe merge this with pixel_buff?


// TODO: rename
//? or public
class stImage : public booba::Image{
public:
    stImage(PixelBuffer* storage, uint x, uint y, uint width, uint height, uint globX, uint globY);
    ~stImage() = default;
    
    virtual uint32_t getH() override;
    virtual uint32_t getX() override;
    virtual uint32_t getPixel(int32_t x, int32_t y) override;
    virtual void putPixel(uint32_t x, uint32_t y, uint32_t color) override;        
    virtual uint32_t& operator()(uint32_t x, uint32_t y) override;
    virtual const uint32_t& operator()(uint32_t x, uint32_t y) const override;
    
    uint globX() const;
    uint globY() const;
private:
    // TODO: rename
    PixelBuffer* storage_;
    uint tmp;

    uint x_, y_;
    uint glob_x_, glob_y_;
    uint width_, height_;
};

#endif // ST_IMAGE_H
