#ifndef WIDGET_H
#define WIDGET_H

#include <list>
// TODO: в этой реализации обработчики добавляются только после того как мы привязываем виджет к окну. Хранить обработчики в виджете мб??
class ContainerWidget;
class Window;
#include "glib_wrapper.h"
#include "Texture.h"
enum class T_EVENT;
class Event;

typedef void (*T_HANDLER_FUNC)(const Event* event);

class Widget{
public:

    Widget(uint x, uint y, uint width, uint height);    
    Widget(ContainerWidget* parent_widget, uint x, uint y, uint width, uint height);    
    ~Widget();

    virtual void fullDraw(); 

    // TODO: избавиться от space'a, ограничить возможность рисования на текущем виджете(чтобы не мог рисовать извне). Если вообще надо рисовать..
    virtual void draw(GraphicSpace* space) = 0;

    void setTexture(const Texture& texture) { texture_ = texture; }

    uint x() const { return x_; }
    uint y() const { return y_; }
    
    uint width() const { return width_; }
    uint height() const { return height_; }

    bool isFocused() const { return focused_; }

    void resize(uint x, uint y, uint width, uint height);

    virtual void onMouseLClickEvent(const Event* event) = 0;
    virtual void onkeyPressedEvent(const Event* event) = 0;
    
private:
    uint      x_, y_;
    uint      gx_, gy_;
    uint      width_, height_;
    
    bool      focused_;
    Texture   texture_;
    //Window*   p_core_window_;
};

#endif // WIDGET_H
