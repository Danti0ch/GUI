#ifndef SLIDER_H
#define SLIDER_H

#include "Widget.h"
#include "RectButton.h"

// TODO: implement possibility to move scroll while pressing scroll main part(by holding mouse button)

//?
// TODO:
/*
class AbstractSlider : public Widget{
public:
    double ratio() const { return ratio_;}

    virtual void onMouseLClick(const MouseLClickEvent* event);
protected:
    double ratio_;
    RectButton<double> butt_;
};
*/

class HSlider : public Widget{
public:
    HSlider(uint x, uint y, uint width, uint height, uint butt_width);
    ~HSlider();

    void onMouseLClick(const MouseLClickEvent* event) override;
    void draw() override;

    // TODO: refactor
    void ratio(double val){
        assert(val >= 0 && val <= 1);

        ratio_ = val;
        RequireRender();
    }
private:
    double ratio_;
    RectButton<HSlider, double> butt_;
};

// TODO: inheritance from containerWidget
class VSlider : public Widget{
public:
    VSlider(uint x, uint y, uint width, uint height, uint butt_height);
    ~VSlider();

    void onMouseLClick(const MouseLClickEvent* event) override;
    void draw() override;

    // TODO: refactor
    void ratio(double val){
        assert(val >= 0 && val <= 1);

        ratio_ = val;
        RequireRender();
    }
private:
    double ratio_;
    RectButton<VSlider, double> butt_;
};
 
#endif // SLIDER_H
