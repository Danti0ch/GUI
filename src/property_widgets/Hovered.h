#ifndef HOVER_HOVER_HHOVER_H
#define HOVER_HOVER_HHOVER_H

#include "Widget.h"

class Hovered : virtual public Widget{
public:
    Hovered(Vector size, const Color& hoverCol, const Color& focusCol);
    Hovered(Vector size);
    ~Hovered();

    virtual void onMouseButtonPressed(const MouseButtonPressedEvent* event) override;
    virtual void onMouseMoved(const MouseMovedEvent* event) override;
    virtual void onMouseButtonReleased(const MouseButtonReleasedEvent* event) override;
protected:
    DrawableArea* hoverLayer_;
    DrawableArea* focusLayer_;
private:
    DrawableArea* defLayer_;

    bool isHoverLayer_;
    bool isFocuseLayer_;
};

#endif // HOVER_HOVER_HHOVER_H
