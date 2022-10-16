#ifndef WIDGET_H
#define WIDGET_H

class Widget{
public:
    // TODO: texture == 0 constructor
    Widget(uint x, uint y, uint width, uint height):
        x_(x), y_(y), width_(width), height_(height), texture_(), p_space_(NULL) {}

    Widget(uint x, uint y, uint width, uint height, const Texture& texture):
        x_(x), y_(y), width_(width), height_(height), texture_(texture), p_space_(NULL) {}
    
    ~Widget(){}

    virtual void fullDraw() /* TODO: final??? */{
        if(p_space_ == NULL) return;
        texture_.draw(p_space_, x_, y_, x_ + width_ - 1, y_ + height_ - 1, TEXTURE_INSERT_MODE::SCRETCHING);
        Draw();
    }

    virtual void draw() = 0;

    void setTexture(const Texture& texture) { texture_ = texture; }

    void linkToSpace(GraphicSpace* p_space) { p_space_ = p_space; }

private:
    // TODO:
    /// @brief координаты виджета (в родителе-окне или в глобальном окне???)
    uint          x_, y_;
    uint          width_, height_;
    
    Texture       texture_;
    
    GraphicSpace* p_space_;
};

#endif // WIDGET_H
