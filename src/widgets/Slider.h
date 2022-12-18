#ifndef SLIDER_H
#define SLIDER_H

#include "Widget.h"
#include "Actions.h"

// TODO: make sliderIndicator hoverable

class Slider : public Widget{
public:
    Slider(Vector size, ORIENTATION orient, ProportionRatio initRatio = 0);
    ~Slider();

    double ratio() const;

    virtual coord indicatorLen() const = 0;
    virtual coord len() const = 0;

    // TODO: to events??
    template<class T_RECEIVER>
    void setHandler(T_RECEIVER* pReceiver, void (T_RECEIVER::*slot)(double)){
        actions_->add(new ObjDynamicArgAction<T_RECEIVER, double>(pReceiver, slot, &this->ratio_));
        return;
    }

    template<class T_RECEIVER>
    void setHandlerIdent(T_RECEIVER* pReceiver, void (T_RECEIVER::*slot)(const Slider*)){
        actions_->add(new ObjArgAction<T_RECEIVER, const Slider*>(pReceiver, slot, this));
        return;
    }
    
    void replaceIndicator(ProportionRatio ratio);

    static Slider* ACTIVE_SLIDER;
protected:
    //?
    double ratio_;

    DrawableArea* indicator_;
    MacroAction* actions_;

    ORIENTATION orient_;
protected:
    void indicatorMove();
    void drawIndicator();
};

class VSlider : public Slider{
public:
    VSlider(coord len, ProportionRatio initRatio = 0);
    VSlider(Vector size, ProportionRatio initRatio = 0);
    ~VSlider() = default;

    void draw() override;

    coord indicatorLen() const override;
    virtual coord len() const override;

    void onMouseButtonPressed(const MouseButtonPressedEvent* event) override;
    void onMouseMoved(const MouseMovedEvent* event) override;
    void onMouseButtonReleased(const MouseButtonReleasedEvent* event) override;

    // TODO:
    //void onMouseWheelScrolled(const MouseWheelScrolledEvent* event) override;
    //?
    //void onKeyPressed(const KeyPressedEvent* event) override;
};

class HSlider : public Slider{
public:
    HSlider(coord len, ProportionRatio initRatio = 0);
    HSlider(Vector size, ProportionRatio initRatio = 0);
    ~HSlider() = default;

    void draw() override;

    coord indicatorLen() const override;
    virtual coord len() const override;

    void onMouseButtonPressed(const MouseButtonPressedEvent* event) override;
    void onMouseMoved(const MouseMovedEvent* event) override;
    void onMouseButtonReleased(const MouseButtonReleasedEvent* event) override;
};

#endif // SLIDER_H
