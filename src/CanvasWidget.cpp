#include "CanvasWidget.h"
#include "EventWrapper.h"

booba::ApplicationContext col_context;
booba::ApplicationContext* APPCONTEXT = &col_context;

CanvasWidget::CanvasWidget(uint width, uint height, ToolManager* tool_manager):
    ExpendedContainerWidget(width, height, 20),
    bg_color_(BLACK),
    fg_color_(RED),
    tool_manager_(tool_manager),
    image_(NULL)
{
    // TODO: remove by adding setting button

    image_ = new stImage(width, height);
    col_context.fgColor = static_cast<uint32_t>(fg_color_);
    col_context.bgColor = static_cast<uint32_t>(bg_color_);
}
CanvasWidget::~CanvasWidget(){}

// TODO: remove copypaste
void CanvasWidget::onMouseLClick(const MouseLClickEvent* event){

    if(!isPointInside(this, event->state()->x(), event->state()->y())) return;
    if(!isVisible()) return;

    tool_manager_->apply(image_, event);
    RequireRender();
    return;
}

void CanvasWidget::onMouseReleased( const MouseReleasedEvent* event){

    if(!isPointInside(this, event->state()->x(), event->state()->y())) return;
    if(!isVisible()) return;

    tool_manager_->apply(image_, event);

    RequireRender();
    return;
}

void CanvasWidget::onMouseMoved(const MouseMovedEvent* event){

    if(!isPointInside(this, event->state()->x(), event->state()->y())) return;
    if(!isVisible()) return;

    tool_manager_->apply(image_, event);

    RequireRender();
    return;
}

void CanvasWidget::connectDataUpdate_(Widget* container){

    image_->setX(real_x());
    image_->setY(real_y());

    ContainerWidget::connectDataUpdate_(container);
}

void CanvasWidget::disconnectDataUpdate_(){

    CanvasWidget::disconnectDataUpdate_();
}

void CanvasWidget::draw(){
    
    ExpendedContainerWidget::draw();
    GetPointerOnPixBuff()->draw(image_);

    return;
}

stImage* CanvasWidget::image(){
    return image_;
}
