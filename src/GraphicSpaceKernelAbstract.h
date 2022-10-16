#ifndef GRAPHIC_SPACE_KERNEL_ABSTRACT_H
#define GRAPHIC_SPACE_KERNEL_ABSTRACT_H

class GraphicSpaceKernelAbstract{

    GraphicSpaceKernelAbstract(uint width, uint height):
        width_(width), height_(height) {}

    virtual void drawText(uint x_pixel, uint y_pixel, const std::string& str, uint font_size, Color col) = 0;
    virtual void drawLine(uint x_pix1, uint y_pix1, uint x_pix2, uint y_pix2, Color col) = 0;
    virtual void drawPixel() = 0;
    virtual void drawPixels() = 0;
    virtual void extractEvent() const = 0;
    virtual void clear() = 0;
    virtual void show() = 0;
    virtual void close() = 0;
    virtual Matrix<Color> GetPixsFromFile(const std::string& filename) const = 0;

    constexpr uint width() const { return width_; }    
    constexpr uint height() const { return height_; }

private:
    uint width_, height_;
};

#endif // GRAPHIC_SPACE_KERNEL_ABSTRACT_H