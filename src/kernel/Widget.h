#ifndef WIDGET_H
#define WIDGET_H

#include "stdlib.h"
#include "Texture.h"
#include "Event.h"
#include "glib_wrapper.h"
#include "logger.h"
#include <list>

//? x and y connect to very close functions by meaning, maybe they should be childs of class dimension_coord?
class Window;
class Widget;
class ContainerWidget;

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

    /// setters
    void x(uint val);
    void y(uint val);
    
    uint real_x() const;
    uint real_y() const;

    uint width() const { return width_; }
    uint height() const { return height_; }

    bool isFocused() const { return is_focused_; }
    bool isVisible() const { return is_visible_; }
    bool isRenderRequired() const { return is_render_required_; }
    Texture& texture(){ return texture_; }
    
    void setTexture(const Texture& texture){ texture_ = texture; }
    
    // TODO: make it virtual for overloading in containerWidget
    void setVisible(bool val){ is_visible_ = val; }

    ContainerWidget* parent() { return parent_widget_; }
    const PixelBuffer& pixBuff() const { return buff_; }
    
    //! normal?? + rename
    PixelBuffer* GetPointerOnPixBuff() { return &buff_; }
    //const EventManager* eventManager() const { return p_manager_; }

    virtual void onMouseLClick(const MouseLClickEvent* event){};
    virtual void onKeyPressed( const KeyPressedEvent* event){};
    virtual void onMouseReleased(const MouseReleasedEvent* event){};
    virtual void onMouseMoved(const MouseMovedEvent* event){};
    
    //? should we remove slider moved
    //! delete if it not be useful in other situations
    virtual void onSliderMoved( const SliderMovedEvent* event){};

    void RequireRender();

    //! not good it is accessible for all widgets
    // or normal?
    void throwEvent(const Event* event);
    void triggerEvent(const Event* event);

    bool isPointInside(uint x, uint y);

    friend class ContainerWidget;
    friend class Window;
private:
    uint x_, y_;
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

#include <list>

class ContainerWidget : public Widget{
public:
    ContainerWidget(uint x, uint y, uint width, uint height);

    virtual void draw() override;


    virtual uint getSubPosX(const Widget* child_widget) const;
    virtual uint getSubPosY(const Widget* child_widget) const;

    // TODO: fix    
    friend class Window;
protected:
    virtual void connect( Widget* child_widget);
    virtual void connect(Widget* child_widget, uint x, uint y);
    virtual void remove( Widget* child_widget);
    
    std::list<Widget*> subwidgets_;
private:
    void connectDataUpdate_(Widget* container) override;
    void disconnectDataUpdate_() override;
};

#endif // WIDGET_H
