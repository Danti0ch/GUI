#ifndef WIDGET_H
#define WIDGET_H

#include "BasicEvents.h"
#include <list>

class ContainerWidget;

button butt("text");

-- расширяемость. Под каждое событие нужно писать свою функцию - обработчик
// TODO: изменить логику хранения ивентов и их добавления в менеджер
class Widget{
public:
    // TODO: texture == 0 constructor
    Widget(uint x, uint y, uint width, uint height, const Window* p_core_window_ = NULL):
        x_(x), y_(y), width_(width), height_(height), texture_(), {
            events_.push_back(new MouseLClickEvent);
            events_.push_back(new KeyPressedEvent);
        }

    ~Widget(){}

    virtual void fullDraw() /* TODO: final??? */{
        texture_.draw(p_core_window_->space, x_, y_, x_ + width_ - 1, y_ + height_ - 1, TEXTURE_INSERT_MODE::SCRETCHING);
        draw();
    }

    virtual void draw() = 0;

    void setTexture(const Texture& texture) { texture_ = texture; }

//  EVENTS
    std::vector<Event*> events;

    friend class ContainerWidget;

private:
    void ConnnectEventsToManager_(){
        if(p_core_window_ == NULL) return;

        for(uint n_event = 0; n_event < events.size(); n_event++){
            p_core_window_->e_manager.addEvent(events[n_event]);
        }
        return;
    }

    void RemoveEventsFromManager_(){
        if(p_core_window_ == NULL) return;

        for(uint n_event = 0; n_event < events.size(); n_event++){
            p_core_window_->e_manager.removeEvent(events[n_event]);
        }
        return;
    }
private:
    // TODO:
    /// @brief координаты виджета (в родителе-окне или в глобальном окне???)
    uint          x_, y_;
    uint          width_, height_;
    
    Texture       texture_;
    Window*       p_core_window_;
};

// TODO: команды для манипулирования приоритезацией рисования
class ContainerWidget : public Widget{
public:
    // TODO: обернуть подобные конструкторы в один макрос
    // TODO: дефолтный параметр для текстуры
    ContainerWidget(uint x, uint y, uint width, uint height):
        Widget(x, y, width, height), subwidgets_(){}

    ContainerWidget(uint x, uint y, uint width, uint height, const Texture& texture):
        Widget(x, y, width, height, texture), subwidgets_(){}
    
    void draw(GraphicSpace* space) override{

        std::list<Widget*>::iterator subwidgets_iter;
        for (subwidgets_iter = subwidgets_.begin(); subwidgets_iter != subwidgets_.end(); subwidgets_iter++){
            (*subwidgets_iter)->fullDraw(space);
        }
        
        return;
    }

    void add(const Widget& child_widget){
        subwidgets_.push_back(&child_widget);
        child_widget.p_core_window_ = p_core_window_;
        child_widget.addEventsToManager()
    }    

    void remove(const Widget& child_widget){
        for i in events:
        subwidgets_.remove(&child_widget);
        child_widget.p_core_window_ = NULL;
    }

private:
    std::list<Widget*> subwidgets_;
};

#endif // WIDGET_H
