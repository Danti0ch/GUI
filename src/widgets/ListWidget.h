#ifndef LIST_WIDGET_H
#define LIST_WIDGET_H

#include "ContainerWidget.h"
#include "RectButton.h"
#include "Slider.h"

//? should it support not specific type widgets
class HListWidget : private ContainerWidget{
public:
    typedef void (*T_HANDLER)();

    HListWidget(uint x, uint y, uint width, uint height, uint elem_width);

    void add(const std::string& label, T_HANDLER p_handler);

    virtual void onSliderMoved( const SliderMovedEvent* event){};

    //? remove??
private:
    uint elem_width_;
    std::vector<RectButton<int>> elems_;
    HSlider slider_;
};

#endif // LIST_WIDGET_H
