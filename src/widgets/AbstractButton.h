#ifndef ABSTRACT_BUTTON_H
#define ABSTRACT_BUTTON_H

#include "Widget.h"
#include "Text.h"

// TODO: add multiple handlers
template<class T_RECEIVER, typename T_HANDLER_ARG>
class AbstractButton : public Widget{
    typedef void (T_RECEIVER::*T_HANDLER)(T_HANDLER_ARG arg);
public:

    //? TODO: remove
    AbstractButton(uint x, uint y, uint width, uint height):
        Widget(x, y, width, height), p_handler_(NULL), p_receiver_(NULL), is_hovered_(false){}

    AbstractButton(const AbstractButton<T_RECEIVER, T_HANDLER_ARG>& other):
        Widget(other.x(), other.y(), other.width(), other.height()),
        p_handler_(other.p_handler_), handler_arg_(other.handler_arg_), is_hovered_(false){}

    void onMouseLClick(const MouseLClickEvent* event) override{

        if(isPointInside(event->state()->x(), event->state()->y())){
            if(p_handler_ == NULL) return;
            (p_receiver_->*p_handler_)(handler_arg_);
        }

        return;
    }

    void onMouseMoved(const MouseMovedEvent* event) override{

        if(isPointInside(event->state()->x(), event->state()->y())){
            // TODO: make it smooth
            if(!is_hovered_){
                is_hovered_ = true;
                
                main_texture_ = texture();
                setTexture(hover_texture_);
                RequireRender();
            }
        }
        else if(is_hovered_){
            is_hovered_ = false;
            setTexture(main_texture_);
            RequireRender();
        }
        return;
    }
    
    bool isHovered() const { return is_hovered_; }

    void setHoverTexture(const Texture& texture){ hover_texture_ = texture; RequireRender(); }

    //? Move to constructor maybe?
    void data(const T_HANDLER_ARG& data){ handler_arg_ = data; }
    void handler(T_RECEIVER* p_receiver, const T_HANDLER handler){ p_receiver_ = p_receiver; p_handler_ = handler; }
private:
    T_RECEIVER*   p_receiver_;
    T_HANDLER     p_handler_;
    T_HANDLER_ARG handler_arg_;

    bool is_hovered_;

    // TODO: refactor
    Texture hover_texture_;
    Texture main_texture_;
};

#endif // ABSTRACT_BUTTON_H
