#ifndef TEXTURE_H
#define TEXTURE_H

#include <set>
#include <string>
#include "Matrix.h"
#include <stdlib.h>
#include "Color.h"
#include "Image.h"
#include "glib_wrapper.h"

enum class TEXTURE_INSERT_MODE{
        FILLING,
        SCRETCHING
};

typedef std::set<std::pair<uint, uint>> pt_set;

class Texture{
public:

    Texture():
        Texture(Color()){}
    
    Texture(const Color& col):
        solid_col_(col), col_pixels_(0, 0), is_solid_(true), transparency_ratio_(1){}

    Texture(const Image& img):
        solid_col_(), col_pixels_(img.data()), is_solid_(false), transparency_ratio_(1){}

    Texture(const Texture& other):
        solid_col_(other.solid_col_), col_pixels_(other.col_pixels_), is_solid_(other.is_solid_), transparency_ratio_(1){}

    ~Texture(){}

    void setTransparency(double val);

    void draw(PixelBuffer* buff, uint x_l, uint y_l, uint x_u, uint y_u, TEXTURE_INSERT_MODE mode = TEXTURE_INSERT_MODE::SCRETCHING);
    void draw(PixelBuffer* buff, uint x_l, uint y_l, uint x_u, uint y_u, const pt_set& mask, TEXTURE_INSERT_MODE mode = TEXTURE_INSERT_MODE::SCRETCHING);

    bool is_solid() const { return is_solid_; }

    const Color& solid_col() const { return solid_col_; }
    const Matrix<Color>& col_pixels() const { return col_pixels_; }

private:
    bool is_solid_;

    double transparency_ratio_;
    // TODO: unused fields
    Color solid_col_;
    Matrix<Color> col_pixels_;
    };

#endif // TEXTURE_H
