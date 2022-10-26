#ifndef GRAPHIC_SPACE_KERNEL_ABSTRACT_H
#define GRAPHIC_SPACE_KERNEL_ABSTRACT_H

#include "Pixel.h"
#include "Color.h"

class Event;
class GraphicSpaceKernelAbstract{

public:
    GraphicSpaceKernelAbstract(uint width, uint height):
        width_(width), height_(height) {}

    virtual void  drawText(uint x_pixel, uint y_pixel, const std::string& str, uint font_size, const Color& col) = 0;
    virtual void  drawLine(uint x_pix1, uint y_pix1, uint x_pix2, uint y_pix2, const Color& col) = 0;
    virtual void  drawPixel(uint x_pix, uint y_pix, const Color& col) = 0;
    virtual void  drawPixels(const std::vector<Pixel>& pixs_to_draw) = 0;
    virtual void  clear(const Color& col) = 0;
    virtual void  show() = 0;
    virtual void  close() = 0;
    virtual bool  isOpen() = 0;
//    virtual Matrix<Color> GetPixsFromFile(const std::string& filename) const = 0;

    virtual bool extractEvent(Event** p_event) = 0;

    constexpr uint width() const { return width_; }
    constexpr uint height() const { return height_; }

private:
    uint width_, height_;
};

#endif // GRAPHIC_SPACE_KERNEL_ABSTRACT_H