#ifndef WINDOW_H
#define WINDOW_H

#include "glib_wrapper.h"
#include "Texture.h"
#include "Widget.h"
#include <string.h>
#include "logger.h"

// TODO: обязательно ли widget != NULL
class EventHandler{

public:

    EventHandler(const Widget* caller_widget, T_HANDLER_FUNC p_handler):
        caller_widget_(caller_widget), p_handler_(p_handler), p_data_(NULL){
            NASSERT(caller_widget);
        }
    EventHandler(const Widget* caller_widget, T_HANDLER_FUNC p_handler, void* p_data):
        EventHandler(caller_widget, p_handler){
            p_data_ = p_data;
            NASSERT(caller_widget);
        }
    ~EventHandler(){
        free(p_data_);
    }

    const Widget*  caller_widget() const { return caller_widget_; }
    T_HANDLER_FUNC handler()       const { return p_handler_; }
    void*          p_data()        const { return p_data_; }
    bool operator==(const EventHandler& other) const{
        if(caller_widget_ == other.caller_widget_ && p_handler_ == other.p_handler_) return true;

        return false;
    }
private:
    const Widget* caller_widget_;
    T_HANDLER_FUNC p_handler_;
    void*           p_data_;
};

class EventManager{
public:
    EventManager():
        handlers_(N_EVENTS){}
    
    void processHandlers(Event* event){
        NASSERT(event);

        std::list<EventHandler>::iterator iter = handlers_[event->id()].begin();

        for(; iter != handlers_[event->id()].end(); iter++){
            if(event->check((*iter).caller_widget())){
                (*iter).handler()(event, (*iter).p_data());
            }
        }
        return;
    }

    void addHandler(T_EVENT event_id, const Widget* caller_widget, const T_HANDLER_FUNC handler, void* p_data){
        NASSERT(caller_widget);
        
        handlers_[(int)event_id].push_back(EventHandler(caller_widget, handler, p_data));
        return;
    }

    void removeHandler(T_EVENT event_id, const Widget* caller_widget, const T_HANDLER_FUNC handler){
        NASSERT(caller_widget);

        std::list<EventHandler>::iterator iter;

        handlers_[(int)event_id].remove(EventHandler(caller_widget, handler));
        return;
    }

    void removeWidgetHandlers(const Widget* caller_widget){
        NASSERT(caller_widget);

        for(uint n_event = 0; n_event < handlers_.size(); n_event++){
            std::list<EventHandler>::iterator iter = handlers_[n_event].begin();

            while(iter != handlers_[n_event].end()){
                if((*iter).caller_widget() == caller_widget){
                    std::list<EventHandler>::iterator iter_to_remove = iter;
                    iter++;
                    handlers_[n_event].erase(iter_to_remove);
                }
                else iter++;
            }
        }
        return;
    }
    ~EventManager(){}
private:
    std::vector<std::list<EventHandler>> handlers_;
};

class Window : public ContainerWidget{
public:

    Window(uint width, uint height):
        space(width, height),
        ContainerWidget(0, 0, width, height)
    {
        p_core_window_ = this;
    }
    
    void exec(){
        Event* event = NULL;
        bool was_event = false;

        fullDraw();
        space.show();

        while(space.isOpen()){
            while(space.extractEvent(&event)){
                was_event = true;
                event_manager.processHandlers(event);
                delete event;
            }
            if(was_event){
                fullDraw();
                space.show();
                was_event = false;
            }
        }

        return;
    }

    friend class Widget;
private:
    GraphicSpace    space;
    EventManager    event_manager;
};

#endif // WINDOW_H
