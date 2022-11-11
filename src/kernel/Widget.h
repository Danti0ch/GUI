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

// TODO: y coord should be from bottom
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
    
    //! normal?? + rename
    PixelBuffer* GetPointerOnPixBuff() { return &buff_; }
    //const EventManager* eventManager() const { return p_manager_; }

    virtual void onMouseLClick(const MouseLClickEvent* event){};
    virtual void onKeyPressed( const KeyPressedEvent* event){};

    //? should we remove slider moved
    //! delete if it not be useful in other situations
    virtual void onSliderMoved( const SliderMovedEvent* event){};

    void RequireRender();
    //! not good it is accessible for all widgets
    // or normal?
    void throwEvent(const Event* event);
    void triggerEvent(const Event* event);
    friend class ContainerWidget;
    friend class Window;
private:
    uint x_, y_;
    uint rx_, ry_;

    uint width_, height_;

    Texture texture_;

    PixelBuffer buff_;

    ContainerWidget* parent_widget_;
    EventManager* p_manager_;

protected:

    bool is_focused_;
    bool is_visible_;
    bool is_render_required_;

private:
    //! TODO: arg to container widget
    virtual void connectDataUpdate_(Widget* container);
    virtual void disconnectDataUpdate_();
};

#endif // WIDGET_H
