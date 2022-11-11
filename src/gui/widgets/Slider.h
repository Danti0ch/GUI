#ifndef SLIDER_H
#define SLIDER_H

#include "ContainerWidget.h"
#include "RectButton.h"

//? slider height could be changable

// private ContainerWidget
class HSlider : public ContainerWidget{
public:
    HSlider(uint x, uint y, uint width, uint height, double visible_area_ratio);

    virtual void onMouseLClick(const MouseLClickEvent* event) override;

private:
    RectButton<double> butt_;
};

#endif // SLIDER_H
