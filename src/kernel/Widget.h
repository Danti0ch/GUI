#ifndef WIDGET_H
#define WIDGET_H

#include "Color.h"
#include "graphicImp.h"
#include <list>
#include <string>
#include "Event.h"
#include "logger.h"

class ContainerWidget;
class Window;

enum class LINKAGE_MODE{

    TOP,
    BOTTOM,
    LEFT,
    RIGHT
};

// TODO: rename to smth connected with pixels, that ctrl+h
/**
 * @brief abstract class for visible entities in application, that realizes general interface methods
 * 
 */

template<class T_WIDGET, class... PROPERTIES>
class ExtWidget : virtual public T_WIDGET, virtual public PROPERTIES...{
public:
    Widget(Vector size);

    //?  
    virtual ~Widget();

    /// @brief get coords of widget, relative to his current parent widget
    Vector pos() const;
    
    /// @brief get coords of widget in the app
    Vector realPos() const;
    
    Vector size() const;

    bool isFocused() const;
    bool isVisible() const;
    
    ContainerWidget* parent();

    void x(coord val);
    void y(coord val);

    void pos(Vector val);

    void visible(bool val);
    void invertVisible();

    void texture(const std::string& path_to_img, bool framed = 0);
    void texture(const Color& col, bool framed = 0);

    void connectBy(Widget* slotWidget, LINKAGE_MODE mode, uint indent_val = 0, int offset = 0);

    static Widget* FOCUSED_WIDGET;

    //?? is it really needed ? test
    void requireRender();
protected:
    virtual void draw() = 0;

    /// @brief executes while widget connecting or disconnecting. Used to change private data.    
    virtual void connectDataUpdate(ContainerWidget* container);
    virtual void disconnectDataUpdate();

    virtual void onMouseButtonPressed(const MouseButtonPressedEvent* event){}
    virtual void onMouseButtonReleased(const MouseButtonReleasedEvent* event){}
    virtual void onMouseMoved(const MouseMovedEvent* event){}
    virtual void onMouseWheelScrolled(const MouseWheelScrolledEvent* event){}
    virtual void onKeyPressed(const KeyPressedEvent* event){}
    virtual void onKeyReleased(const KeyReleasedEvent* event){}

private:
    /// @brief smth changed in widget, there could be neccesity in redrawing it
    bool isRenderRequired();

    /// @brief every widget has background that should be drawed before other things of widget will be drawen
    void bLayerDraw();

    void triggerEvent(const Event* event);
protected:
    DrawableArea* bgLayer_;
    RenderObject* buffer_;

    bool focusable_;

    /// @brief if cur widget contains subwidget, returns its pos on the buffer of current widget. Otherwise returns poison
    virtual Vector subPos(const Widget* subwidget) const;

private:
    Vector relPos_;
    Vector size_;

    ContainerWidget* parent_widget_;

    bool is_focused_;
    bool is_visible_;
    bool is_render_required_;
    
    Window* window_;
friend class ContainerWidget;
friend class EventManager;
friend class Window;

// TODO: remove
friend class Expended;
friend class Contexted;
};

bool isPointInside(const Widget* widget, Vector pos);
bool isPointInside(const RectangleArea& rect, Vector pos);

/**
 * @brief container for multiple widgets
 * 
 */
class ContainerWidget : public Widget{
public:
    ContainerWidget(Vector size);
    ~ContainerWidget() = default;

protected:
    virtual void connect(Widget* child_widget, Vector pos);
    virtual void remove( Widget* child_widget);

    virtual void draw() override;

    virtual void connectDataUpdate(ContainerWidget* container) override;
    virtual void disconnectDataUpdate() override;

    virtual Vector subPos(const Widget* subwidget) const override;

protected:
    std::list<Widget*> subwidgets_;
friend class Widget;
};

/**
 * @brief class that distributes events on containing widgets
*/
class EventManager{
public:
    EventManager();
    ~EventManager() = default;

    void addWidget(Widget* widget);
    void removeWidget(Widget* widget);
    void ProcessHandlers(const Event* event);

private:
    std::list<Widget*> widgets_;
};

#endif // WIDGET_H
