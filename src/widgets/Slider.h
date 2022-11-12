#ifndef SLIDER_H
#define SLIDER_H

#include "Widget.h"

// TODO: implement possibility to move scroll while pressing scroll main part(by holding mouse button)
class AbstractSlider : public Widget{
public:

    void onMouseLClick() override;
    double ratio() const { return ratio_;}
private:
    double ratio_;
};

class HSlider : public Widget{
public:
    HSlider(uint x, uint y, uint width, uint height);
    ~HSlider();

    double ratio() const { return ratio_;}
private:
    double ratio_;
};

#endif // SLIDER_H
