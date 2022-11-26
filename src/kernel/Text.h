#ifndef TEXT_H
#define TEXT_H

#include "Color.h"
#include "glib_wrapper.h"

/*
enum class ALIGNMENT{
    CENTER,
    LEFT,
    RIGHT
};
*/

// TODO: many lines text placing
// TODO: alignment with different modes

const uint DEFAULT_TEXT_OFFSET_X = 8;

class Text{
public:

    Text():
        data_(), font_size_(default_font_size), col_(0, 0, 0){}
    
    Text(const std::string& data):
        data_(data), font_size_(default_font_size), col_(0, 0, 0){}
    
    void data(const std::string& data){ data_ = data; }
    void fontSize(uint font_size){ font_size_ = font_size; }
    void color(const Color& col){ col_ = col; }
    
    void draw(PixelBuffer* space, uint x_pixel, uint y_pixel){

        space->drawText(x_pixel, y_pixel, data_, font_size_, col_);
        return;
    }

    void draw(PixelBuffer* space){
        // assuming that text will get only one line at widget

        uint y_coord = space->height() / 2 - font_size_ / 2;
        uint x_coord = DEFAULT_TEXT_OFFSET_X;

        space->drawText(x_coord, y_coord, data_, font_size_, col_);
        return;
    }

    static uint default_font_size;

private:
    uint        font_size_;
    std::string data_;
    Color       col_;    
};

#endif // TEXT_H
