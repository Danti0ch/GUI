#include "Hovered.h"

Hovered::Hovered(Vector size):
    Widget(size),
    hoverLayer_(CREATE_DRAWABLE_AREA(size)),
    focusLayer_(CREATE_DRAWABLE_AREA(size)),
    isHoverLayer_(false),
    isFocuseLayer_(false),
    defLayer_(bgLayer_)
{}

Hovered::Hovered(Vector size, const Color& hoverCol, const Color& focusCol):
    Hovered(size)
{
    hoverLayer_->clear(hoverCol);
    focusLayer_->clear(focusCol);
}

Hovered::~Hovered(){
    delete hoverLayer_;
    delete focusLayer_;
}

void Hovered::onMouseButtonPressed(const MouseButtonPressedEvent* event){
    if(isFocuseLayer_) return;

    bgLayer_ = focusLayer_;
    isFocuseLayer_ = true;

    requireRender();
    return;
}

void Hovered::onMouseMoved(const MouseMovedEvent* event){

    bool pointInside = isPointInside(this, event->newPos());

    if(isHoverLayer_ && !pointInside){
        bgLayer_ = defLayer_;
        isHoverLayer_ = false;

        requireRender();
    }
    else if(pointInside){
        bgLayer_ = hoverLayer_;
        isHoverLayer_ = true;

        requireRender();
    }
    return;
}
