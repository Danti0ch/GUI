#ifndef SLIDER_H
#define SLIDER_H

#include "Widget.h"
#include "Actions.h"

// TODO: make sliderIndicator hoverable

class Slider : public Widget{
public:
    Slider(Vector size);
    ~Slider();

    double ratio() const;

    virtual coord indicatorLen() = 0;

    template<class T_RECEIVER>
    void setHandler(T_RECEIVER* pReceiver, void (T_RECEIVER::*slot)(double));
protected:
    //?
    double ratio_;

    DrawableArea* indicator_;
    MacroAction* actions_;
protected:
    void indicatorMove(ORIENTATION orient);
    void drawIndicator(ORIENTATION orient);
};

class VSlider : public Slider{
public:
    VSlider(coord len);
    VSlider(Vector size);
    ~VSlider() = default;

    void draw() override;

    coord indicatorLen() override;

    void onMouseButtonPressed(const MouseButtonPressedEvent* event) override;
    void onMouseMoved(const MouseMovedEvent* event) override;
    
    // TODO:
    //void onMouseWheelScrolled(const MouseWheelScrolledEvent* event) override;
    //?
    //void onKeyPressed(const KeyPressedEvent* event) override;
};

class HSlider : public Slider{
public:
    HSlider(coord len);
    HSlider(Vector size);
    ~HSlider() = default;

    void draw() override;

    coord indicatorLen() override;

    void onMouseButtonPressed(const MouseButtonPressedEvent* event) override;
    void onMouseMoved(const MouseMovedEvent* event) override;
};

#endif // SLIDER_H
