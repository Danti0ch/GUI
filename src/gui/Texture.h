#ifndef TEXTURE_H
#define TEXTURE_H

enum class TEXTURE_INSERT_MODE{
        FILLING,
        SCRETCHING
};

class Texture{

    Texture(const Color& col = Color::WHITE):
        solid_col_(col), col_pixels_(0, 0), is_solid_(true) {}

    Texture(const Image& img):
        solid_col_(), col_pixels_(img.data()), is_solid_(false) {}

    Texture(const Texture& other):
        solid_col_(other.solid_col_), col_pixels_(other.col_pixels_), is_solid_(other.is_solid_){}

    ~Texture(){}

    void draw(GraphicSpace* space, uint x_l, uint y_l, uint x_u, uint y_u, TEXTURE_INSERT_MODE mode = TEXTURE_INSERT_MODE::SCRETCHING);
    void draw(GraphicSpace* space, uint x_l, uint y_l, uint x_u, uint y_u, const std::set& mask, TEXTURE_INSERT_MODE mode = TEXTURE_INSERT_MODE::SCRETCHING);

    bool is_solid() const { return is_solid_; }

public:
    static Texture SOLID_WHITE(Color::WHITE);
private:

    bool is_solid_;

    // TODO: unused fields
    Color solid_col_;
    Matrix<Color> col_pixels_;
};

#endif // TEXTURE_H
