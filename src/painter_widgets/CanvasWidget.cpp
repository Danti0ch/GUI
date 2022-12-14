#include "CanvasWidget.h"
#include "EventWrapper.h"

CanvasWidget::CanvasWidget(Vector size, ToolManager* tool_manager):
    Expended(size),
    tool_manager_(tool_manager),
    drawableLayer_(CREATE_DRAWABLE_AREA(size))
{}
CanvasWidget::~CanvasWidget(){
    delete drawableLayer_;
}

void CanvasWidget::onMouseButtonPressed(const MouseButtonPressedEvent* event){
    if(!isPointInside(this, ManipulatorsContext::activeContext.mousePos())) return;

    tool_manager_->apply(this, event);
    requireRender();
    return;
}

void CanvasWidget::onMouseButtonReleased(const MouseButtonReleasedEvent* event){
    if(!isPointInside(this, ManipulatorsContext::activeContext.mousePos())) return;

    tool_manager_->apply(this, event);
    requireRender();
    return;
}

void CanvasWidget::onMouseMoved(const MouseMovedEvent* event){
    if(!isPointInside(this, ManipulatorsContext::activeContext.mousePos())) return;

    tool_manager_->apply(this, event);
    requireRender();
    return;
}

void CanvasWidget::draw(){
    
    Expended::draw();

    buffer_->draw({0, 0}, drawableLayer_);
    return;
}

DrawableArea* CanvasWidget::drawableLayer(){

    return drawableLayer_;
}
