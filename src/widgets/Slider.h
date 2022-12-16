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

    coord indicatorLen() const override;
    virtual coord len() const override;

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

    coord indicatorLen() const override;
    virtual coord len() const override;

    void onMouseButtonPressed(const MouseButtonPressedEvent* event) override;
    void onMouseMoved(const MouseMovedEvent* event) override;
};

#endif // SLIDER_H
