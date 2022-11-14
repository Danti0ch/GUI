#ifndef DRAWABLE_AREA_H
#define DRAWABLE_AREA_H

#include "Widget.h"

// now it would be able to draw black lines and that's all
class DrawableArea : public Widget{
public:
    DrawableArea(uint x, uint y, uint width, uint height);

    void onMouseReleased(const MouseReleasedEvent* event) override;
    void onMouseMoved(const MouseMovedEvent* event) override;
    
    void draw() override;
private:
    bool is_drawing_enabled;
};

#endif // DRAWABLE_AREA_H
