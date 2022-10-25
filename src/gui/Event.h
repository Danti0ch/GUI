#ifndef EVENT_H
#define EVENT_H


template<T_ARG> class Event{
    typedef void(*p_handler)(const T_ARG& arg) T_HANDLER;
public:

    Event(T_CORE_EVENT core_id, const Widget* p_widget):
        handlers_(), p_widget_(p_widget), core_id_(core_id){
    }

    ~Event(){}

    void addHandler(T_HANDLER p_handler){
        handlers_.push_back(p_handler);
        return;
    }

    void proccessHandlers(const T_ARG& arg){
        for(uint n_handler = 0; n_handler < handlers_.size(); n_handler++){
            handlers_[n_handler](arg);
        }
        return;
    }

    T_CORE_EVENT core_id() const { return core_id_; }

    const Widget*  getWidget() const { return p_widget_; }

    bool apply(const CoreEvent* core_event){
        return core_event->check(getWidget());
    }
private:
    std::vector<T_HANDLER> handlers_;
    T_CORE_EVENT           core_id_; 
    Widget*                p_widget_;
    vector<T_CORE_EVENT>   core_event_ids_;
};

/*
// TODO: rename if dont work
class Event{
    typedef void(*p_handler)() T_HANDLER;
public:

    Event(T_CORE_EVENT core_id):
        handlers_(), core_id_(core_id){
        }


//    Event(const Widget* p_widget, T_HANDLER p_handler):
  //      handlers_(1, p_handler), p_widget_(p_widget){}
    
    ~Event(){}

    void addHandler(T_HANDLER p_handler){
        handlers_.push_back(p_handler);
        return;
    }

    void proccessHandlers(const T_ARG& arg){
        for(uint n_handler = 0; n_handler < handlers_.size(); n_handler++){
            handlers_[n_handler](arg);
        }
        return;
    }

    T_CORE_EVENT core_id() const { return core_id_; }
private:
    std::vector<T_HANDLER> handlers_;
    T_CORE_EVENT           core_id_; 
};
*/
#endif // EVENT_H
