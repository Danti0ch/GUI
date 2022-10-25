#ifndef IMAGE_H
#define IMAGE_H

#include "glib_wrapper.h"

class Image{
public:
    //Image(const std::string& filename):
    //    data_(GetPixsFromFile(filename)){}
    
    Image(const Matrix<Color>& storage):
        data_(storage){}
    
    Image(const Image& other):
        data_(other.data_){}
    
    ~Image(){}

    Matrix<Color> data() const { return data_; }
private:
    Matrix<Color> data_;
};

#endif // IMAGE_H
