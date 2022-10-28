#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

typedef void (*T_HANDLER_FUNC)(const Event* event);

class EventHandler{

public:
    EventHandler(const Widget* caller_widget, T_HANDLER_FUNC p_handler):
        caller_widget_(caller_widget), p_handler_(p_handler){
            NASSERT(caller_widget);
        }
    ~EventHandler(){}

    const Widget*  caller_widget() const { return caller_widget_; }
    T_HANDLER_FUNC handler()       const { return p_handler_; }

    bool operator==(const EventHandler& other) const{
        if(caller_widget_ == other.caller_widget_ && p_handler_ == other.p_handler_) return true;

        return false;
    }
private:
    const Widget* caller_widget_;
    T_HANDLER_FUNC p_handler_;
};

// TODO:
/**
 * @brief 
 * 
 */
class EventManager{
public:
    EventManager():
        handlers_(N_EVENTS){}
    
    void processHandlers(const Event* event){
        NASSERT(event);

        std::list<EventHandler>::iterator iter = handlers_[event->id()].begin();

        for(; iter != handlers_[event->id()].end(); iter++){
            if(event->check((*iter).caller_widget())){
                (*iter).handler()(event);
            }
        }
        return;
    }

    void addHandler(T_EVENT event_id, const Widget* caller_widget, const T_HANDLER_FUNC handler){
        NASSERT(caller_widget);
        
        handlers_[(int)event_id].push_back(EventHandler(caller_widget, handler));
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
    std::vector<std::list<Widget>> handlers_;
};

#endif // EVENT_MANAGER_H
