// TODO: rename
#ifndef LOC_PIX_BUFFER_H
#define LOC_PIX_BUFFER_H

#include "glib_wrapper.h"

class LocPixBuffer{
public:
    LocPixBuffer(PixBuffer* p_buf, uint x, uint y, uint width, uint height);
    LocPixBuffer(const LocPixBuffer& p_locbuf, uint x, uint y, uint width, uint height);

    void drawText(uint x_pixel, uint y_pixel, const std::string& str, uint font_size, const Color& col);
    void drawLine(uint x_pix1, uint y_pix1, uint x_pix2, uint y_pix2, const Color& col);
    void drawPixel(uint x_pix, uint y_pix, const Color& col);
    void drawPixels(const std::vector<Pixel>& pixels);
    
private:
    PixBuffer* p_buf_;
    
    uint x_, y_;
    uint width_, height_;
};

#endif // LOC_PIX_BUFFER_H
