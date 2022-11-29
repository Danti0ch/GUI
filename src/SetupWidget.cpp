#include "SetupWidget.h"
#include "CanvasManager.h"

SetupWidget::SetupWidget(ToolManager* tool_manager):
    ExpendedContainerWidget(200, 200, 10),
    tool_manager_(tool_manager){}

void SetupWidget::onMouseLClick(const MouseLClickEvent* event){
    if(!isPointInside(this, event->state()->x(), event->state()->y())) return;
    if(!isVisible()) return;

    tool_manager_->apply(CanvasManager::ACTIVE_CANVAS_WIDGET->image(), event);
    RequireRender();
}

void SetupWidget::onKeyPressed( const KeyPressedEvent* event){
    if(!isVisible()) return;

    tool_manager_->apply(CanvasManager::ACTIVE_CANVAS_WIDGET->image(), event);
    RequireRender();
}

void SetupWidget::onMouseReleased(const MouseReleasedEvent* event){
    if(!isPointInside(this, event->state()->x(), event->state()->y())) return;
    if(!isVisible()) return;

    tool_manager_->apply(CanvasManager::ACTIVE_CANVAS_WIDGET->image(), event);
    RequireRender();
}

void SetupWidget::onMouseMoved(const MouseMovedEvent* event){
    if(!isPointInside(this, event->state()->x(), event->state()->y())) return;
    if(!isVisible()) return;

    tool_manager_->apply(CanvasManager::ACTIVE_CANVAS_WIDGET->image(), event);
    RequireRender();
}


void SetupWidget::onSliderMoved( const SliderMovedEvent* event){


    std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA!\n";
    if(!isVisible()) return;

    tool_manager_->apply(CanvasManager::ACTIVE_CANVAS_WIDGET->image(), event);
    RequireRender();
}
