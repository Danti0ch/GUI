#ifndef TEXT_H
#define TEXT_H

#include "Color.h"
#include "glib_wrapper.h"

class Text{
public:

    Text():
        data_(), font_size_(12), col_(){}
    
    Text(const std::string& data):
        data_(data), font_size_(12), col_(){}
    
    void data(const std::string& data){ data_ = data; }
    void fontSize(uint font_size){ font_size_ = font_size; }
    void color(const Color& col){ col_ = col; }
    
    void draw(GraphicSpace* space, uint x_pixel, uint y_pixel){
        space->drawText(x_pixel, y_pixel, data_, font_size_, col_);
        return;
    }

private:
    uint        font_size_;
    std::string data_;
    Color       col_;    
};

#endif // TEXT_H
