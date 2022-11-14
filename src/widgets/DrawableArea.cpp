#include "DrawableArea.h"

DrawableArea::DrawableArea(uint x, uint y, uint width, uint height):
    Widget(x, y, width, height),
    is_drawing_enabled(false){}

void DrawableArea::onMouseReleased(const MouseReleasedEvent* event){
    is_drawing_enabled = false;
    return;
}

void DrawableArea::onMouseMoved(const MouseMovedEvent* event){
    return;
}

void DrawableArea::draw(){
    return;
}
