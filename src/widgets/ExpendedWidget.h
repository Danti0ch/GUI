#ifndef EXP_WIDGET_H
#define EXP_WIDGET_H

#include "Widget.h"
#include "Slider.h"

// TODO: make slider 
class ExpendedWidget : public Widget{
public:
    ExpendedWidget(uint x, uint y, uint width, uint height, uint sliderWidth);
    ~ExpendedWidget();

    void onSliderMoved( const SliderMovedEvent* event) override;

    virtual void draw() override;

    void ext_width( uint val);
    void ext_height(uint val);
private:

    //? maybe implement new renderttexture buffer for drawing all subwidgets at once
    HSlider hSlider_;
    VSlider vSlider_;

    uint loc_x_, loc_y_;
    uint ext_width_, ext_height_;
};

#endif // EXP_WIDGET_H
