#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

// TOOD: зачем???
class EventManager{
public:
    EventManager():
        core_widget_(){}

    void addWidget(const Widget* widget){
        widgets_.push_back(widget);
        return;
    }

    void removeWidget(const Widget* widget){
        widgets_.remove(widget);
        return;
    }

    void ProcessHandlers(const Event* event){

        std::list<EventHandler>::iterator iter = widgets_.begin();

        for(; iter != widgets_.end(); iter++){
            if(event->check(*iter)){
                if(event.id() == T_EVENT::mouseLClickEvent){
                    widget->onMouseLClick(event->x(), event->y());
                }
                else if(event.id() == T_EVENT::keyPressedEvent){
                    widget->onKeyPressed(event->key());
                }
            }
        }
        return;
    }

private:
    std::list<Widget*> widgets_;
}

#endif // EVENT_MANAGER_H
