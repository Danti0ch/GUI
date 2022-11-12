#ifndef LIST_WIDGET_H
#define LIST_WIDGET_H

#include "Widget.h"
#include "RectButton.h"
#include "Slider.h"
#include "ExpendedContainerWidget.h"

//? should it support not specific type widgets

// TODO: add remove
template<typename T_ARG>
class AbstractListWidget : public ExpendedContainerWidget{
public:
    typedef void (*T_HANDLER)();

    AbstractListWidget(uint x, uint y, uint width, uint height, uint elem_size);

    virtual void add(const std::string& label, T_HANDLER p_handler, const T_ARG& arg) = 0;

    //? ok
    void connect(Widget* child_widget) = delete;
    void remove( Widget* child_widget) = delete;
    
protected:
    std::vector<RectButton<T_ARG>> elems_;
private:
    uint elem_size_;
};

template<typename T_ARG>
class HListWidget : public AbstractListWidget<T_ARG>{
public:
    typedef void (*T_HANDLER)();

    HListWidget(uint x, uint y, uint width, uint height, uint elem_width);

    void add(const std::string& label, T_HANDLER p_handler, const T_ARG& arg) override;
};

template<typename T_ARG>
class VListWidget : public AbstractListWidget<T_ARG>{
public:
    typedef void (*T_HANDLER)();

    VListWidget(uint x, uint y, uint width, uint height, uint elem_height);

    void add(const std::string& label, T_HANDLER p_handler, const T_ARG& arg) override;
};

#endif // LIST_WIDGET_H
