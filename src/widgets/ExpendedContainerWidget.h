/**
 * @file ExtendedWidget.h
 * @brief same as containerWidget, but the area is expanded by using sliderWidget
 * @version 0.1
 * @date 2022-11-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef EXP_CONTAINER_WIDGET_H
#define EXP_CONTAINER_WIDGET_H

#include "Widget.h"
#include "Slider.h"

// TODO: make only horizontal or vertical movement widgets
class ExpendedContainerWidget : public ContainerWidget{
public:
    ExpendedContainerWidget(uint x, uint y, uint width, uint height, uint sliderWidth);
    ~ExpendedContainerWidget();

    void onSliderMoved( const SliderMovedEvent* event) override;

    virtual void draw() override;
    //virtual void connect(Widget* child_widget, uint x, uint y);
    virtual void connect(Widget* child_widget);
    virtual void remove(Widget* child_widget);
    
private:

    //? maybe implement new renderttexture buffer for drawing all subwidgets at once
    HSlider hSlider_;
    VSlider vSlider_;

    uint loc_x_, loc_y_;
    uint ext_width_, ext_height_;
};

#endif // EXP_CONTAINER_WIDGET_H
