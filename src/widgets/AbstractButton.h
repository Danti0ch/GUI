#ifndef ABSTRACT_BUTTON_H
#define ABSTRACT_BUTTON_H

#include "Widget.h"
#include "Text.h"

// TODO: add multiple handlers
template<typename T_HANDLER_ARG>
class AbstractButton : public Widget{
    typedef void (*T_HANDLER)(T_HANDLER_ARG arg);
public:

    //? TODO: remove
    AbstractButton(uint x, uint y, uint width, uint height):
        Widget(x, y, width, height), p_handler_(NULL){}

    AbstractButton(const AbstractButton<T_HANDLER_ARG>& other):
        Widget(other.x(), other.y(), other.width(), other.height()),
        p_handler_(other.p_handler_), handler_arg_(other.handler_arg_){}

    void onMouseLClick(const MouseLClickEvent* event) override{
        if(p_handler_ == NULL) return;
        p_handler_(handler_arg_);
        return;
    }

    void data(const T_HANDLER_ARG& data){ handler_arg_ = data; }
    void handler(const T_HANDLER handler){ p_handler_ = handler; }
private:
    T_HANDLER     p_handler_;
    T_HANDLER_ARG handler_arg_;
};

#endif // ABSTRACT_BUTTON_H
