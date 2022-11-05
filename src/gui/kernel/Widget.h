#ifndef WIDGET_H
#define WIDGET_H

#include "stdlib.h"
#include "Texture.h"
#include "Event.h"
#include "glib_wrapper.h"
#include "EventManager.h"

class ContainerWidget;
class Window;
class Widget;

class EventManager{
public:
    EventManager();
    void addWidget(Widget* widget);
    void removeWidget(Widget* widget);
    void ProcessHandlers(const Event* event);

private:
    std::list<Widget*> widgets_;
};

/**
 * @brief an abstract class of any entity that has a representation on the application screen
 * 
 */
class Widget{
public:

    Widget(uint x, uint y, uint width, uint height);    
    ~Widget();

    virtual void coreDraw() final;
    virtual void draw() = 0;

    uint x() const { return x_; }
    uint y() const { return y_; }

//    uint glob_x() const { return gx_; }
//    uint glob_y() const { return gy_; }

    uint width() const { return width_; }
    uint height() const { return height_; }

    bool isFocused() const { return is_focused_; }
    bool isVisible() const { return is_visible_; }
    bool isRenderRequired() const { return is_render_required_; }
    const Texture& texture(){ return texture_; }
    void setTexture(const Texture& texture){ texture_ = texture; }

    ContainerWidget* parent() { return parent_widget_; }
    const PixelBuffer& pixBuff() const { return buff_; }

    virtual void onMouseLClick(const Event* event){};
    virtual void onKeyPressed( const Event* event){};
    
    void triggerEvent(const Event* event);
    friend class ContainerWidget;
private:
    uint x_, y_;

    // TODO: понадобятся ли локальные координаты виджета, или достаточно текущих глобальных?(x_, y_)
    //uint glob_x_, glob_y_;

    uint width_, height_;

    bool is_focused_;
    bool is_visible_;
    bool is_render_required_;

    Texture texture_;

    PixelBuffer buff_;

    // TODO: remove mb?
    EventManager* p_manager_;
    // TODO: needed?
    ContainerWidget* parent_widget_;

private:
    virtual void connectToManager_(EventManager* manager);
    virtual void disconnectFromManager_();
};

#endif // WIDGET_H
