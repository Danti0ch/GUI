#ifndef ST_IMAGE_H
#define ST_IMAGE_H

#include "tools.hpp"
#include "glib_wrapper.h"
//? maybe merge this with pixel_buff?

// TODO: rename
//? or public
class stImage : protected booba::Image{
public:
    stImage(uint width, uint height);
    uint32_t getH() override;
    uint32_t getX() override;
    uint32_t getPixel(int32_t x, int32_t y) override;
    void putPixel(uint32_t x, uint32_t y, uint32_t color) override;        
    uint32_t& operator()(uint32_t x, uint32_t y);
    const uint32_t& operator()(uint32_t x, uint32_t y) const;

protected:
    ~stImage() override;
    
private:
    // TODO: rename
    PixelBuffer storage_;
};

#endif // ST_IMAGE_H
