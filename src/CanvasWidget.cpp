#include "CanvasWidget.h"
#include "stImage.h"
#include "EventWrapper.h"

booba::ApplicationContext col_context;
booba::ApplicationContext* APPCONTEXT = &col_context;

CanvasWidget::CanvasWidget(uint width, uint height, ToolManager* tool_manager):
    ExpendedContainerWidget(width, height, 20),
    bg_color_(BLACK),
    fg_color_(RED),
    tool_manager_(tool_manager)
{
    // TODO: remove by adding setting button

    col_context.fgColor = static_cast<uint32_t>(fg_color_);
    col_context.bgColor = static_cast<uint32_t>(bg_color_);
}
CanvasWidget::~CanvasWidget(){}

// TODO: remove copypaste
void CanvasWidget::onMouseLClick(const MouseLClickEvent* event){
    if(!isVisible()) return;

    stImage wrapper(exp_buf_, loc_x_, loc_y_, width(), height(), real_x(), real_y());
    tool_manager_->apply(&wrapper, event);
    RequireRender();
    return;
}

void CanvasWidget::onMouseReleased( const MouseReleasedEvent* event){
    if(!isVisible()) return;

    stImage wrapper(exp_buf_, loc_x_, loc_y_, width(), height(), real_x(), real_y());
    tool_manager_->apply(&wrapper, event);

    RequireRender();
    return;
}

void CanvasWidget::onMouseMoved(const MouseMovedEvent* event){

    if(!isVisible()) return;
    stImage wrapper(exp_buf_, loc_x_, loc_y_, width(), height(), real_x(), real_y());
    tool_manager_->apply(&wrapper, event);

    RequireRender();
    return;
}
