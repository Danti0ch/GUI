#ifndef WIDGET_H
#define WIDGET_H

/**
 * @brief an abstract class of any entity that has a representation on the application screen
 * 
 */
class Widget{
public:

    Widget(uint x, uint y, uint width, uint height);    
    ~Widget();

    void         coreDraw(LocPixBuffer* buf) final;
    virtual void draw(LocPixBuffer* buf) = 0;

    uint x() const { return x_; }
    uint y() const { return y_; }

    uint glob_x() const { return gx_; }
    uint glob_y() const { return gy_; }

    uint width() const { return width_; }
    uint height() const { return height_; }

    bool isFocused() const { return is_focused_; }
    bool isVisible() const { return is_visible_; }

    void setTexture(const Texture& texture){ texture_ = texture; }

    virtual void connect(ContainerWidget* parent) = 0;
    virtual void remove_connect() = 0;

    virtual void onMouseLClick(const Event* event) = 0;
    virtual void onKeyPressed( const Event* event) = 0;
    
private:
    uint x_, y_;

    // TODO: понадобятся ли локальные координаты виджета, или достаточно текущих глобальных?(x_, y_)
    //uint glob_x_, glob_y_;

    uint width_, height_;

    bool is_focused_;
    bool is_visible_;

    Texture texture_;

    ContainerWidget* parent_widget_;
};

#endif // WIDGET_H
