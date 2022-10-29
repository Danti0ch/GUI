#include "LocPixBuffer.h"

LocPixBuffer::LocPixBuffer(PixBuffer* p_buf, uint x, uint y, uint width, uint height):
    p_buf_(p_buf), x_(x), y_(y), width_(width), height_(height)
{
    // TODO: точно так стоит обрабатывать?
    if(width_ > p_buf_->width() || height_ > p_buf_->height()) throw std::out_of_range("");
}

LocPixBuffer::LocPixBuffer(const LocPixBuffer& p_locbuf, uint x, uint y, uint width, uint height):
    LocPixBuffer(p_locbuf.p_buf_, x + p_locbuf.x_, y + p_locbuf.y_, width, height)
{
    if(x_ + width_ > p_locbuf.width_ || y_ + height_ > p_locbuf.height_) throw std::out_of_range("");
}

void LocPixBuffer::drawText(uint x_pixel, uint y_pixel, const std::string& str, uint font_size, const Color& col){
    if(x_pixel >= width_ || y_pixel >= height_) throw std::out_of_range(""):
    p_buf_->drawText(x_pixel + x_, y_pixel + y_, str, font_size, col);
    return;
}

void LocPixBuffer::drawLine(uint x_pix1, uint y_pix1, uint x_pix2, uint y_pix2, const Color& col){
    
    if(x_pix1 >= width_ || x_pix2 >= width_ || y_pix1 >= height_ || y_pix2 >= height_) throw std::out_of_range("");
    p_buf_->drawLine(x_ + x_pix1, y_ + y_pix1, x_ + x_pix2, y_ + y_pix2, col);
    return;
}

void LocPixBuffer::drawPixel(uint x_pix, uint y_pix, const Color& col){
    
    if(x_pix >= width_ || y_pix >= height_) throw std::out_of_range("");
    p_buf->drawPixel(x_ + x_pix, y_ + y_pix, col);
    return;
}

// TODO: долго ?
void LocPixBuffer::drawPixels(const std::vector<Pixel>& pixels){

    std::vector<Pixel> offset_pixels = pixels;

    for(uint n_pixel = 0; n_pixel < offset_pixels.size(); n_pixel++){

        if(offset_pixels[n_pixel].x() >= width_ || offset_pixels[n_pixel].y() >= height_) throw std::out_of_range("");
        offset_pixels[n_pixel].x() += x_;
        offset_pixels[n_pixel].y() += y_;
    }

    p_buf->drawPixels(offset_pixels);
    return;
}
