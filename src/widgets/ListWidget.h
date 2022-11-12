#ifndef LIST_WIDGET_H
#define LIST_WIDGET_H

#include "Widget.h"
#include "RectButton.h"
#include "Slider.h"

//? should it support not specific type widgets

template<typename T_ARG>
class AbstractListWidget : public ExtendedContainerWidget{
public:
    typedef void (*T_HANDLER)();

    AbstractListWidget(uint x, uint y, uint width, uint height, uint elem_size);

    virtual void add(const std::string& label, T_HANDLER p_handler, const T_ARG& arg) = 0;

    //? ok
    void connect(Widget* child_widget) = delete;
    void remove( Widget* child_widget) = delete;
    
private:
    uint elem_size_;
    std::vector<RectButton<int>> elems_;
};

template<typename T_ARG>
class HListWidget : public AbstractListWidget{
public:
    typedef void (*T_HANDLER)();

    HListWidget(uint x, uint y, uint width, uint height, uint elem_width);

    void add(const std::string& label, T_HANDLER p_handler, const T_ARG& arg) override;

    void draw() override;
};

template<typename T_ARG>
class VListWidget : public AbstractListWidget{
public:
    typedef void (*T_HANDLER)();

    VListWidget(uint x, uint y, uint width, uint height, uint elem_height);

    void add(const std::string& label, T_HANDLER p_handler, const T_ARG& arg) override;

    void draw() override;
};

#endif // LIST_WIDGET_H
