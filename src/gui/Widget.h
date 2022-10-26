#ifndef WIDGET_H
#define WIDGET_H

#include <list>
// TODO: в этой реализации обработчики добавляются только после того как мы привязываем виджет к окну. Хранить обработчики в виджете мб??
class ContainerWidget;
class Window;
#include "glib_wrapper.h"
#include "Texture.h"
#include <string.h>

enum class T_EVENT;
class Event;

typedef void (*T_HANDLER_FUNC)(Event* event, void* p_data);

class Widget{
public:
    // TODO: texture == 0 constructor
    Widget(uint x, uint y, uint width, uint height);    
    Widget(ContainerWidget* parent_widget, uint x, uint y, uint width, uint height);    
    ~Widget();

    virtual void fullDraw(); 
    // TODO: without const...
    virtual void draw() = 0;

    void setTexture(const Texture& texture) { texture_ = texture; }

    template<typename T_ARG>
    bool addEventHandler(T_EVENT event_id, T_HANDLER_FUNC p_handler, T_ARG arg){
        if(p_core_window_ == NULL) return false;

        void* p_copied_data = calloc(1, sizeof(T_ARG));
        memcpy((char*)p_copied_data, (char*)(&arg), sizeof(T_ARG));

        manager->addHandler(event_id, this, p_handler, p_copied_data);
        return true;
    }

    bool addEventHandler(T_EVENT event_id, T_HANDLER_FUNC p_handler);

    bool RemoveEventHandler(T_EVENT event_id, T_HANDLER_FUNC p_handler);

    uint x() const { return x_; }
    uint y() const { return y_; }
    
    uint width() const { return width_; }
    uint height() const { return height_; }

    bool isFocused() const { return focused_; }

    void resize(uint x, uint y, uint width, uint height);

    bool is_visible() const { return is_visible_; }

    GraphicSpace* space() { return space_; }

    friend class Window;
    friend class ContainerWidget;
private:
    // TODO:
    /// @brief координаты виджета (в родителе-окне или в глобальном окне???)
    uint          x_, y_;
    uint          gx_, gy_;
    uint          width_, height_;
    
    bool          focused_;
    bool          is_visible_;
    Texture       texture_;
    
    GraphicSpace* space_;
    EventManager* manager_;
};

// TODO: команды для манипулирования приоритезацией рисования
class ContainerWidget : public Widget{
public:
    // TODO: обернуть подобные конструкторы в один макрос
    // TODO: дефолтный параметр для текстуры
    ContainerWidget(ContainerWidget* parent_widget, uint x, uint y, uint width, uint height);
    ContainerWidget(uint x, uint y, uint width, uint height);

    void draw() override;

    void connect(Widget& child_widget);
    void remove(Widget& child_widget);
private:
    std::list<Widget*> subwidgets_;
};

#endif // WIDGET_H
